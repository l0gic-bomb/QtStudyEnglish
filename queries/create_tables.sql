CREATE TABLE verbs ( id INTEGER, form_1 TEXT, form_2 TEXT, form_3 TEXT, translation TEXT, points INTEGER, constraint PK_VERB primary key (id));
CREATE TABLE nouns ( id INTEGER, word TEXT, translation TEXT, points INTEGER, constraint PK_NOUN primary key (id));
CREATE TABLE adjectives ( id INTEGER, word TEXT, translation TEXT, points INTEGER, constraint PK_ADJECTIVE primary key (id));