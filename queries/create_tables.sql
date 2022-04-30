/*==============================================================*/
/* Table: verbs                                                 */
/*==============================================================*/
CREATE TABLE verbs 
{
	id int;
	form_1 text,
	form_2 text,
	form_3 text,
	translation text,
	points int,
	constraint PK_CARD primary key (id)
};

/*==============================================================*/
/* Table: nouns                                                 */
/*==============================================================*/
CREATE TABLE nouns
{
	id int;
	word text;
	translation text,
	points int,
	constraint PK_CARD primary key (id)
};

/*==============================================================*/
/* Table: adjectives                                            */
/*==============================================================*/
CREATE TABLE adjectives
{
	id int;
	word text;
	translation text,
	points int,
	constraint PK_CARD primary key (id)	
};