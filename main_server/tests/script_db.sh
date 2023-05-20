#!/usr/bin/env bash

#for file in data/*.json
#do
#    filename=$(basename $file _data.json)
#    cat $file | jq -c '.[]' > "data/${filename}_import.json"
#done

# создаем базу данных
psql -U postgres -f create_db.sql

# заполняем базу данных json данными
psql -U postgres -d test-db -f fill_db.sql

rm -rf data/*_import.json
