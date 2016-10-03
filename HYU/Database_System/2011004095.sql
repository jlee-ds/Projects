CREATE TABLE maintext(
	m_id INT UNSIGNED AUTO_INCREMENT,
	title VARCHAR(200) NOT NULL,
	m_writer VARCHAR(20) NOT NULL,
	m_date DATETIME NOT NULL,
	hits INT UNSIGNED DEFAULT '0' NOT NULL,
	m_content TEXT,
	password VARCHAR(20) BINARY NOT NULL,
	PRIMARY KEY(m_id)
);

CREATE TABLE comment(
	c_id INT UNSIGNED AUTO_INCREMENT,
	c_writer VARCHAR(20) NOT NULL,
	c_date DATETIME NOT NULL,
	c_content VARCHAR(256) NOT NULL,
	m_id INT UNSIGNED NOT NULL,
	PRIMARY KEY(c_id),
	FOREIGN KEY(m_id) REFERENCES maintext(m_id) ON DELETE CASCADE
);

INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle1','writer1','2013-11-01 00:00:00','testcontent1','psw1');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle2','writer2','2013-11-02 00:00:00','testcontent2','psw2');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle3','writer3','2013-11-03 00:00:00','testcontent3','psw3');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle4','writer4','2013-11-04 00:00:00','testcontent4','psw4');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle5','writer5','2013-11-05 00:00:00','testcontent5','psw5');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle6','writer6','2013-11-06 00:00:00','testcontent6','psw6');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle7','writer7','2013-11-07 00:00:00','testcontent7','psw7');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle8','writer8','2013-11-08 00:00:00','testcontent8','psw8');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle9','writer9','2013-11-09 00:00:00','testcontent9','psw9');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle10','writer10','2013-11-10 00:00:00','testcontent10','psw10');
INSERT INTO maintext(title,m_writer,m_date,m_content,password) VALUES ('testtitle11','writer11','2013-11-11 00:00:00','testcontent11','psw11');

