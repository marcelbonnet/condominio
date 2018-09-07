PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "unidades" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`numero`	TEXT NOT NULL UNIQUE,
	`resp_financeiro`	TEXT NOT NULL,
	`resp_financeiro_email`	TEXT NOT NULL,
	`resp_financeiro_telefone`	INTEGER
);
CREATE TABLE IF NOT EXISTS "rateios" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`fk_unidade`	INTEGER NOT NULL,
	`valor`	INTEGER NOT NULL,
	`parcela`	INTEGER NOT NULL,
	`dt_vcto`	DATE NOT NULL,
	`razao`	NUMERIC NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES `unidades`(`id`)
);
CREATE TABLE `descontos` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`valor`	INTEGER NOT NULL,
	`fk_unidade`	INTEGER NOT NULL,
	`memo`	TEXT NOT NULL,
	`fk_despesa`	INTEGER NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES unidades('id'),
	FOREIGN KEY(`fk_despesa`) REFERENCES despesas('id')
);
CREATE TABLE IF NOT EXISTS "despesas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`dt_evento`	DATE NOT NULL,
	`valor`	INTEGER NOT NULL,
	`memo`	TEXT NOT NULL,
	`dt_inclusao`	DATE NOT NULL,
	`nota`	BLOB
);
CREATE TABLE `livro_ocorrencias` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`fk_unidade`	INTEGER NOT NULL,
	`memo`	TEXT NOT NULL,
	`dt_evento`	DATETIME NOT NULL,
	`dt_inclusao`	DATETIME NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES unidades('id')
);
CREATE TABLE `livro_atas` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`documento`	BLOB NOT NULL,
	`memo`	TEXT NOT NULL,
	`dt_documento`	DATE NOT NULL,
	`dt_inclusao`	DATETIME NOT NULL
);
CREATE TABLE IF NOT EXISTS "assinaturas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`fk_unidade`	INTEGER NOT NULL,
	`fk_livro_ata`	INTEGER,
	`fk_livro_ocorrencias`	INTEGER,
	FOREIGN KEY(`fk_unidade`) REFERENCES `unidades`(`id`),
	FOREIGN KEY(`fk_livro_ata`) REFERENCES `livro_atas`(`id`),
	FOREIGN KEY(`fk_livro_ocorrencias`) REFERENCES livro_ocorrencias('id')
);
CREATE TABLE IF NOT EXISTS "cobrancas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`dt_vcto`	DATE NOT NULL,
	`valor`	INTEGER NOT NULL,
	`fk_unidade`	INTEGER NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES `unidades`(`id`)
);
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('unidades',6);
INSERT INTO sqlite_sequence VALUES('rateios',0);
INSERT INTO sqlite_sequence VALUES('despesas',0);
INSERT INTO sqlite_sequence VALUES('assinaturas',0);
INSERT INTO sqlite_sequence VALUES('cobrancas',0);
COMMIT;
