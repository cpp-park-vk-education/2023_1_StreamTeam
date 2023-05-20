\c "test-db"

\cd data

CREATE UNLOGGED TABLE IF NOT EXISTS users_import(data jsonb);
\copy users_import FROM 'users_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS rooms_import(data jsonb);
\copy rooms_import FROM 'rooms_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS films_import(data jsonb);
\copy films_import FROM 'films_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS viewers_import(data jsonb);
\copy viewers_import FROM 'viewers_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS messages_import(data jsonb);
\copy messages_import FROM 'messages_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS bids_import(data jsonb);
\copy bids_import FROM 'bids_import.json'

CREATE UNLOGGED TABLE IF NOT EXISTS votes_import(data jsonb);
\copy votes_import FROM 'votes_import.json'

INSERT INTO users (username, email, "password")
SELECT data->>'username', data->>'email', data->>'password'
FROM users_import;

INSERT INTO films (name, link, "info")
SELECT data->>'name', (data->>'link')::text, (data->>'info')::jsonb
FROM films_import;

INSERT INTO rooms (name, creator, current_film)
SELECT data->>'name', (data->>'creator')::int, (data->>'current_film')::int
FROM rooms_import;

INSERT INTO viewers (id_user, id_room, points, "role")
SELECT (data->>'id_user')::int, (data->>'id_room')::int, (data->>'points')::int, (data->>'role')::viewer_role
FROM viewers_import;

INSERT INTO messages (id_room, id_user, message)
SELECT (data->>'id_room')::int, (data->>'id_user')::int, data->>'message'
FROM messages_import;

INSERT INTO bids (id_creator, id_room, "text", min_points, begin_time, lifetime)
SELECT (data->>'id_creator')::int, (data->>'id_room')::int, data->>'text', (data->>'min_points')::int, (data->>'begin_time')::timestamp, (data->>'lifetime')::time
FROM bids_import;

INSERT INTO votes (id_bid, id_user, vote, points)
SELECT (data->>'id_bid')::int, (data->>'id_user')::int, (data->>'vote')::boolean, (data->>'points')::int
FROM votes_import;

SELECT * FROM users;
SELECT * FROM films;
SELECT * FROM rooms;
SELECT * FROM messages;
SELECT * FROM viewers;
SELECT * FROM bids;
SELECT * FROM votes;

DROP TABLE users_import;
DROP TABLE films_import;
DROP TABLE rooms_import;
DROP TABLE messages_import;
DROP TABLE viewers_import;
DROP TABLE bids_import;
DROP TABLE votes_import;

\cd ..

\c postgres
