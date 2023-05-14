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
    password varchar(64) NOT NULL
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
    created_at timestamp NOT NULL DEFAULT NOW(),
    FOREIGN KEY (id_room) REFERENCES rooms (id),
    FOREIGN KEY (id_user) REFERENCES users (id)
);

CREATE TYPE viewer_role AS ENUM ('admin', 'moderator', 'guest', 'left', 'banned');

CREATE TABLE viewers (
    id serial PRIMARY KEY NOT NULL,
    id_user integer NOT NULL,
    id_room integer NOT NULL,
    points integer,
    role viewer_role NOT NULL,
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
    begin_time timestamp NOT NULL DEFAULT NOW(),
    FOREIGN KEY (id_creator) REFERENCES users (id),
    FOREIGN KEY (id_room) REFERENCES rooms (id)
);

CREATE TABLE votes (
    id serial PRIMARY KEY NOT NULL,
    id_bid integer NOT NULL,
    id_user integer NOT NULL,
    vote boolean NOT NULL,
    points integer NOT NULL,
    FOREIGN KEY (id_bid) REFERENCES bids (id),
    FOREIGN KEY (id_user) REFERENCES users (id)
);

\c postgres
