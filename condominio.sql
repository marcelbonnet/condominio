CREATE TABLE sqlite_sequence(name,seq);
CREATE TABLE `descontos` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`valor`	INTEGER NOT NULL,
	`fk_unidade`	INTEGER NOT NULL,
	`memo`	TEXT NOT NULL,
	`fk_despesa`	INTEGER NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES unidades('id'),
	FOREIGN KEY(`fk_despesa`) REFERENCES despesas('id')
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
CREATE TABLE IF NOT EXISTS "unidades" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`numero`	TEXT NOT NULL UNIQUE,
	`resp_financeiro`	TEXT NOT NULL,
	`resp_financeiro_email`	TEXT NOT NULL,
	`resp_financeiro_telefone`	TEXT
);
CREATE TABLE IF NOT EXISTS "grupo_despesas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`grupo`	TEXT NOT NULL UNIQUE
);
CREATE TABLE IF NOT EXISTS "despesas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`dt_evento`	DATE NOT NULL,
	`valor`	INTEGER NOT NULL,
	`memo`	TEXT NOT NULL,
	`dt_inclusao`	DATE NOT NULL,
	`nota`	BLOB,
	`fkNatureza`	INTEGER NOT NULL,
	`fkGrupo`	INTEGER,
	FOREIGN KEY(`fkNatureza`) REFERENCES `natureza_despesas`(`id`),
	FOREIGN KEY(`fkGrupo`) REFERENCES `grupo_despesas`(`id`)
);
CREATE TABLE IF NOT EXISTS "natureza_despesas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`natureza`	TEXT NOT NULL UNIQUE,
	`fkGrupo`	INTEGER,
	FOREIGN KEY(`fkGrupo`) REFERENCES `grupo_despesas`(`id`)
);
CREATE TABLE IF NOT EXISTS "rateios" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`fk_unidade`	INTEGER NOT NULL,
	`valor`	INTEGER NOT NULL,
	`parcela`	INTEGER NOT NULL,
	`dt_vcto`	DATE NOT NULL,
	`razao`	NUMERIC NOT NULL,
	`fkDespesa`	INTEGER NOT NULL,
	FOREIGN KEY(`fk_unidade`) REFERENCES `unidades`(`id`),
	FOREIGN KEY(`fkDespesa`) REFERENCES `despesas`(`id`)
);
