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

DROP INDEX IF EXISTS votes_user_bid_index;
DROP INDEX IF EXISTS films_name_index;
DROP INDEX IF EXISTS bids_room_index;

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
    data jsonb
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

\c postgres
