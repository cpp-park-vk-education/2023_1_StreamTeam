DROP DATABASE IF EXISTS "test-db";
CREATE DATABASE "test-db";

COMMENT ON DATABASE "test-db" IS 'Test db for vk project';

\c "test-db"

DROP TABLE IF EXISTS votes;
DROP TABLE IF EXISTS bids;
DROP TABLE IF EXISTS viewers;
DROP TABLE IF EXISTS rooms;
DROP TABLE IF EXISTS users;

DROP TYPE IF EXISTS viewer_role;

CREATE TABLE users (
    id serial PRIMARY KEY NOT NULL,
    username varchar(32) NOT NULL,
    email varchar(64) NOT NULL,
    password varchar(64) NOT NULL
);

CREATE TABLE rooms (
    id serial PRIMARY KEY NOT NULL,
    name varchar(64) NOT NULL,
    creator integer NOT NULL,
    FOREIGN KEY (creator) REFERENCES users (id)
);

CREATE TYPE viewer_role AS ENUM ('admin', 'moderator', 'guest', 'banned');

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
    begin_time timestamp NOT NULL,       -- в insert now() ?
    lifetime time NOT NULL,
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
