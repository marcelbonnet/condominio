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
CREATE TABLE IF NOT EXISTS "unidades" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`numero`	TEXT NOT NULL UNIQUE,
	`resp_financeiro`	TEXT NOT NULL,
	`resp_financeiro_email`	TEXT NOT NULL UNIQUE,
	`resp_financeiro_telefone`	TEXT,
	`email2`	TEXT UNIQUE
);
CREATE VIEW view_despesas AS SELECT d.id, d.dt_evento, d.valor, d.memo, d.dt_inclusao, nd.id AS naturezaId, gd.id AS grupoId, nd.natureza, gd.grupo FROM despesas d LEFT JOIN natureza_despesas nd ON nd.id = d.fkNatureza LEFT JOIN grupo_despesas gd ON gd.id = nd.fkGrupo
/* view_despesas(id,dt_evento,valor,memo,dt_inclusao,naturezaId,grupoId,natureza,grupo) */;
CREATE VIEW view_rateios AS SELECT u.id AS unidadeId, u.numero, r.id AS rateioId, r.fk_unidade, r.parcela, r.razao, r.valor, r.fkDespesa, r.dt_vcto
FROM unidades u
LEFT OUTER JOIN rateios r ON u.id = r.fk_unidade
/* view_rateios(unidadeId,numero,rateioId,fk_unidade,parcela,razao,valor,fkDespesa,dt_vcto) */;
CREATE TABLE IF NOT EXISTS "cobrancas_rateios" (
	`fkCobranca`	INTEGER NOT NULL,
	`fkRateio`	INTEGER NOT NULL,
	FOREIGN KEY(`fkCobranca`) REFERENCES `cobrancas`(`id`),
	FOREIGN KEY(`fkRateio`) REFERENCES `rateios`(`id`)
);
CREATE UNIQUE INDEX `uniqueindex_cobrancas_rateios` ON `cobrancas_rateios` (`fkCobranca` ,`fkRateio` )
;
CREATE TABLE IF NOT EXISTS "cobrancas" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`dt_vcto`	DATE NOT NULL,
	`valor`	INTEGER NOT NULL,
	`fk_unidade`	INTEGER NOT NULL,
	`dt_pgto`	INTEGER,
	`valor_pgto`	INTEGER,
	FOREIGN KEY(`fk_unidade`) REFERENCES `unidades`(`id`)
);
