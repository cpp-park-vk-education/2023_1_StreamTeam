DROP DATABASE IF EXISTS "test-db";
CREATE DATABASE "test-db";

COMMENT ON DATABASE "test-db" IS 'Test db for vk project';

\c "test-db"

DROP TABLE IF EXISTS votes;
DROP TABLE IF EXISTS bids;
DROP TABLE IF EXISTS viewers;
DROP TABLE IF EXISTS messages;
DROP TABLE IF EXISTS rooms;
DROP TABLE IF EXISTS films;
DROP TABLE IF EXISTS users;

DROP TYPE IF EXISTS viewer_role;

CREATE TABLE users (
    id serial PRIMARY KEY NOT NULL,
    username varchar(32) NOT NULL UNIQUE,
    email varchar(64) NOT NULL UNIQUE,
    password varchar(64) NOT NULL   -- тип изменится на BYTEA при хэшировании
);

CREATE TABLE films (
    id serial PRIMARY KEY NOT NULL,
    name varchar(256) NOT NULL,
    link text NOT NULL UNIQUE,
    info jsonb
);

CREATE TABLE rooms (
    id serial PRIMARY KEY NOT NULL,
    name varchar(256) NOT NULL,
    creator integer NOT NULL,
    current_film integer,
    FOREIGN KEY (creator) REFERENCES users (id),
    FOREIGN KEY (current_film) REFERENCES films (id)
);

CREATE TABLE messages (
    id serial PRIMARY KEY NOT NULL,
    id_room integer NOT NULL,
    id_user integer NOT NULL,
    message text NOT NULL,
    created_at timestamp(0) NOT NULL DEFAULT NOW(),
    FOREIGN KEY (id_room) REFERENCES rooms (id),
    FOREIGN KEY (id_user) REFERENCES users (id)
);

CREATE TYPE viewer_role AS ENUM ('admin', 'moderator', 'guest', 'left', 'banned');

CREATE TABLE viewers (
    id serial PRIMARY KEY NOT NULL,
    id_user integer NOT NULL,
    id_room integer NOT NULL,
    points integer NOT NULL,
    role viewer_role NOT NULL,
    UNIQUE (id_user, id_room),
    FOREIGN KEY (id_user) REFERENCES users (id),
    FOREIGN KEY (id_room) REFERENCES rooms (id)
);

CREATE TABLE bids (
    id serial PRIMARY KEY NOT NULL,
    id_creator integer NOT NULL,
    id_room integer NOT NULL,
    text text NOT NULL,
    min_points integer NOT NULL,
    lifetime time NOT NULL,
    begin_time timestamp(0) NOT NULL DEFAULT NOW(),
    FOREIGN KEY (id_creator) REFERENCES users (id),
    FOREIGN KEY (id_room) REFERENCES rooms (id)
);

CREATE TABLE votes (
    id serial PRIMARY KEY NOT NULL,
    id_bid integer NOT NULL,
    id_user integer NOT NULL,
    vote boolean NOT NULL,
    points integer NOT NULL,
    UNIQUE (id_bid, id_user),
    FOREIGN KEY (id_bid) REFERENCES bids (id),
    FOREIGN KEY (id_user) REFERENCES users (id)
);

CREATE INDEX bids_room_index ON bids (id_room);
CREATE INDEX votes_user_bid_index ON votes (id_user, id_bid);
CREATE INDEX films_name_index ON films USING gin(to_tsvector('russian', name));

CREATE OR REPLACE FUNCTION message_validation() RETURNS TRIGGER AS $message_validation$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        IF (
            EXISTS (
            SELECT * FROM viewers
            WHERE id_user=NEW.id_user AND id_room=NEW.id_room AND role NOT IN ('left', 'banned'))
        ) 
        THEN 
            RAISE NOTICE 'Сообщение успешно добавлено.';
            RETURN NEW;
        ELSE 
            RAISE EXCEPTION 'Ошибка: невозможно добавить сообщение.';
        END IF;
    ELSIF (TG_OP = 'UPDATE') THEN
        IF (
            OLD.id_user != NEW.id_user OR OLD.id_room != NEW.id_room OR OLD.created_at != NEW.created_at
        )
        THEN
            RAISE EXCEPTION 'Ошибка: данные поля менять нельзя.';
        ELSE
            RETURN NEW;
        END IF;
    END IF;
    RETURN NULL;
END;

$message_validation$ LANGUAGE plpgsql;

CREATE TRIGGER message_validation_trigger
AFTER INSERT OR UPDATE ON messages
FOR EACH ROW EXECUTE PROCEDURE message_validation();

CREATE OR REPLACE FUNCTION bids_validation() RETURNS TRIGGER AS $bids_validation$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        IF (
            EXISTS (
            SELECT * FROM viewers
            WHERE id_user=NEW.id_creator AND id_room=NEW.id_room AND role IN ('admin', 'moderator'))
        ) 
        THEN 
            RAISE NOTICE 'Ставка успешно добавлена.';
            RETURN NEW;
        ELSE 
            RAISE EXCEPTION 'Ошибка: невозможно добавить ставку.';
        END IF;
    ELSIF (TG_OP = 'UPDATE') THEN
        IF (
            OLD.id_creator != NEW.id_creator OR OLD.id_room != NEW.id_room OR OLD.begin_time != NEW.begin_time
        )
        THEN
            RAISE EXCEPTION 'Ошибка: данные поля менять нельзя.';
        ELSE
            RETURN NEW;
        END IF;
    END IF;
    RETURN NULL;
END;

$bids_validation$ LANGUAGE plpgsql;

CREATE TRIGGER bids_validation_trigger
AFTER INSERT OR UPDATE ON bids
FOR EACH ROW EXECUTE PROCEDURE bids_validation();

CREATE OR REPLACE FUNCTION votes_validation() RETURNS TRIGGER AS $votes_validation$
BEGIN
    IF NEW.points < (
            SELECT min_points FROM bids 
            WHERE id = NEW.id_bid)
    THEN
        RAISE EXCEPTION 'Ошибка: неверное количество очков.';
    END IF;

    IF NOW() <= (
            SELECT begin_time + lifetime FROM bids 
            WHERE id = NEW.id_bid)
    THEN
        RAISE EXCEPTION 'Ошибка: ставка уже закрыта.';
    END IF;

    IF (TG_OP = 'INSERT') THEN
        IF (
            EXISTS (
                SELECT * FROM viewers, bids
                WHERE bids.id_room = viewers.id_room AND bids.id = NEW.id_bid AND viewers.id_user = NEW.id_user
                AND viewers.role NOT IN ('banned', 'left'))
        ) 
        THEN 
            RAISE NOTICE 'Голос успешно добавлен.';
            RETURN NEW;
        ELSE 
            RAISE EXCEPTION 'Ошибка: невозможно добавить голос.';
        END IF;
    ELSIF (TG_OP = 'UPDATE') THEN
        IF (
            OLD.id_bid != NEW.id_bid OR OLD.id_user != NEW.id_user
        )
        THEN
            RAISE EXCEPTION 'Ошибка: данные поля менять нельзя.';
        ELSE
            RETURN NEW;
        END IF;
    END IF;
    RETURN NULL;
END;

$votes_validation$ LANGUAGE plpgsql;

CREATE TRIGGER votes_validation_trigger
AFTER INSERT OR UPDATE ON votes
FOR EACH ROW EXECUTE PROCEDURE votes_validation();

\c postgres
