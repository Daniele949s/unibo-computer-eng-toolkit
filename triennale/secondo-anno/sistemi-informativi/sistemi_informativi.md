# Funzioni di base SQL

## Creazione database e tabelle
```sql
DROP TABLE *nomeTabella*;


CREATE TABLE *nomeTabella*(
	*nomeAttributo*  *tipo*  *vincoli* ,
	...
);
```

## Tipi di dato
```sql
  - integer
  - char(*num*)          				-- precisamente *num* caratteri salvati in memoria
  - varchar						-- in automatico max = 8000
  - varchar(*num*)       				-- max *num* caratteri salvati in memoria
  - dec( *cifre intere* , *cifre decimali*)
  - date
  - time
  - datetime
  - year
```

## Vincoli di integrità
```sql
  - NOT NULL							-- l'attributo necessita un valore
  - PRIMARY KEY							-- chiave primaria singola, mettere sempre dopo NOT NULL
  - FOREIGN KEY REFERENCES *tabella*(*attrTabella*)
  - UNIQUE							-- valore dell'attributo unico su tutta la tabella oppure null
  - CHECK(*controllo*)						-- esegue un controllo nel dato inserito, possibile metterlo anche in fondo alla creazione della tabella
  - DEFAULT *valore*						-- se non inserito, l'attributo assume questo valore
--
-- FONDO DELLA CREAZIONE TABELLA:
  
  - CONSTRAINT							-- posso denominare un vincolo con un nome specifico
  - PRIMARY KEY (*val1*, *val2*, ...)				-- crea una superchiave
  - FOREIGN KEY (*attr*) REFERENCES *tabella*(*attrTabella*)    -- crea un riferimento ad un attributo di una tabella

  esempio
  CREATE TABLE Auto(
	Targa char(7) NOT NULL PRIMARY KEY,
	Modello varchar(30) NOT NULL,
	CodR varchar(30) NOT NULL,
	PrezzoVendita DEC(8,2) NOT NULL,
	Km integer NOT NULL,
	Anno integer NOT NULL,
	Venduta char(2),
	
	CONSTRAINT ControlloVendita CHECK (Venduta='SI'),
	
	FOREIGN KEY (Modello) REFERENCES Modelli(Modello),
	FOREIGN KEY (CodR) REFERENCES Rivenditori(CodR)
  );
```

## Inserimento dati

```sql

INSERT INTO *tabella* VALUES (*val1*, *val2*, ... , *valN*);
INSERT INTO *tabella* (*val1*, *val2*) VALUES (*val1*, *val2*);    	-- Posso scegliere di inserire solo determinati valori, non tutti (occhio ai vincoli NOT NULL)

```

# Operazioni di base su tabelle

## Sottrazione tra tabelle

```sql
query 1
EXCEPT
query 2
```

### Data attuale
```sql
CURRENT TIMESTAMP
```

### Utente attuale
```sql
CURRENT USER
```

## Modifica tabella con finestra
```sql
UPDATE VARIABILI
SET Valore = :newValue
WHERE Nome = :nomeVar;
```

## Doppia WITH
```sql
WITH A(...) AS (
  ....
),
B(...) AS (
  ....
)
*query*
```


# Funzioni aggregate

Servono ad ottenere dal DB informazioni di sintesi che caratterizzano “gruppi” di tuple
ES: il numero di esami del corso 913, la media dei voti dello studente 29323, la media dei voti per tutti i corsi del primo anno ...

Generano un risultato dalla tabella scelta e filtrata con FROM e WHERE
## OPERATORI
```sql
- **COUNT(* / *attributo*)**  
  Conta le tuple (o se datogli un attributo, tutte le righe con quel valore non nullo)
- **MIN(*attributo*)**  
  Restituisce il minimo
- **MAX(*attributo*)**  
  Restituisce il massimo
- **SUM(*attributo*)**  
  Restituisce la somma
- **AVG(*attributo*)**  
  Restituisce la media
- **DISTINCT**  
  Viene messo prima dell'attributo, evita che l'aggregatore prenda valori già visti

```

### Esempi

```sql
-- Somma stipendi degli impiegati nella sede S01
SELECT SUM(Stipendio) AS Somma
FROM Imp
WHERE Sede = ‘S01’

-- Somma tutti gli stipendi diversi degli impiegati nella sede S01
SELECT SUM(DISTINCT Stipendio)
FROM Imp
WHERE Sede = ‘S01’

-- Alcuni operatori necessitano di un CASTING (anche implicito) per rappresentare il giusto tipo di valore
-- es. avg è di tipo decimal ma stipendio nella tabella era integer
SELECT AVG(Stipendio/1.0) AS AvgStip
FROM Imp
```

## GROUP BY

Quando uso un aggregatore, nella select potrò mettere solo altri aggregatori, altrimenti il mio sistema non saprebbe più su che base raggruppare.
Altrimenti, posso scegliere io i criteri tramite GROUP BY.

```sql
SELECT Sede, COUNT(*) AS NumProg
FROM Imp
WHERE Ruolo = ‘Programmatore’
GROUP BY Sede
```

Tutti gli attributi usati per raggruppare devono comparire nella SELECT.

## HAVING

Spesso è utile eseguire altre proiezioni dopo aver raggruppato, ma ormai la SELECT è già stata eseguita prima della GROUP BY.
E' stato quindi implementato HAVING, un ulteriore batteria di controlli eseguita come ultima fase della query.

```sql
-- Il numero di impiegati di ogni sede che ha lo stipendio max <= 2000
SELECT Sede, COUNT(*) AS NumImp
FROM Imp
GROUP BY Sede
HAVING MAX(Stipendio) <= 2000
```

# Suequery

In una query, eseguo confronto tra dati della tabella e il risultato di un'altra query annidata

## SUBQUERY SCALARI

La subquery ritorna un singolo valore

```sql
  es. impiegati con stipendio minimo
  
  SELECT CodImp
  FROM Imp
  WHERE Stipendio = ( SELECT MIN(Stipendio) FROM Imp )
```

## SUBQUERY LISTA

Restituiscono una colonna, una lista di valori

```sql
  - <op> corrisponde a = , <= , >= ...

  - <op> ANY / IN    (la relazione <op> vale per almeno uno dei valori)
  - <op> ALL         (la relazione <op> vale per tutti i valori)
  - precedenti


  -- es. impiegati con stipendio minimo
  
  SELECT CodImp
  FROM Imp
  WHERE Stipendio <= ALL ( SELECT Stipendio FROM Imp )

```

## SUBQUERY CORRELATE

Il blocco esterno "passa" qualcosa come variabile al blocco interno
Si ha quindi un esecuzione simile ad un Ciclo FOR

### OPERATORI
```sql
  - EXISTS / NOT EXISTS  (Vero se la query "ha restituito / non ha restituito" qualcosa)
  - precedenti


  --es. sedi con almeno un programmatore
  SELECT Sede
  FROM Sedi S
  WHERE EXISTS ( SELECT * FROM Imp WHERE Ruolo = ‘Programmatore’ AND Sede = S.Sede )


  --es. Sedi in cui sono presenti tutti i ruoli == a Sedi in cui non esiste un ruolo non presente  (DIVISIONE)
  SELECT Sede FROM Sedi S
  WHERE NOT EXISTS ( SELECT * FROM Imp I1
                     WHERE NOT EXISTS (SELECT * FROM Imp I2
                                       WHERE S.Sede = I2.Sede
                                       AND I1.Ruolo = I2.Ruolo))
```

# Trigger

I trigger vengono tipicamente usati per gestire vincoli di integrità, calcolare dati derivati, gestire eccezioni.
Esempio rapido:

```sql
CREATE OR REPLACE TRIGGER XXXXX
BEFORE INSERT ON __TAB_CON_FK__
REFERENCING NEW AS N
FOR EACH ROW
WHEN( EXISTS ( 
    SELECT *
    FROM __TAB1__
    WHERE N.__FK__ = TAB1.__KEY__
    AND __TAB1__.TIPO = 1
) ) SIGNAL SQLSTATE '70001' ('La tupla referenzia una tupla che non appartiene a __TAB_FIGLIA__!');
```

## SINTASSI

```sql
   CREATE OR REPLACE *nomeTrigger*								-- Definizione del trigger, gli assegna un nome

   (opzionale) NO CASCADE BEFORE INSERT ON *tabella*   						-- Evita reazioni a catena di trigger (si mette quasi sempre)

												-- v  v  v  EVENTO  v  v  v

   *BEFORE/AFTER* *INSERT/UPDATE/DELETE* OF *attributo_della_tabella* ON *tabella*		-- Indica l'evento effettivo che andrà a scaturire il trigger (quando accade, dove)
												-- before --> si usa per condizionare l'esito dell'operazione, che potrei anche bloccare
												-- after  --> agisco sulle conseguenze dei cambiamenti che ho già applicato

   REFERENCING *NEW / OLD / NEW_TABLE / OLD_TABLE* AS *nome*     				-- Indica lo stato del dato/tabella su cui si sta agendo, prima/dopo dell'azione eseguita
												-- OLD e OLD_TABLE non hanno senso cogli INSERT        NEW e NEW_TABLE non hanno senso coi DELETE

   *FOR EACH ROW / FOR EACH STATEMENT*                                          		-- Posso agire sulle singole righe modificate nel target  (es. per controllare che tutti gli update siano legali)
												-- Oppure considerare tutta l'azione come un gruppo       (es. per contare quanti inserimenti sono stati eseguiti)

   WHEN [subquery condizione]   	                                 		        -- Condiziona l'esecuzione dell'azione

												-- v  v  v  AZIONE (a scelta)  v  v  v

   SIGNAL SQLSTATE '*codiceEccezione* (*testo eccezione*)					-- Annullo gli effetti dell'azione che ha scaturito il trigger segnalo l'errore

   SELECT, INSERT, DELETE, UPDATE								-- Vado ad agire direttamente sulle tabelle da aggiornare

												-- v  v  v  CONDIZIONI E AZIONI ESCLUSIVE  v  v  v
   IF *subquery condizione*									-- A differenza del WHEN posso distinguere cosa fare quando il controllo risulta "Vero" o "Falso"
   THEN *conseguenza 1*;
   ELSE *conseguenza 2*;
   END IF
```

## ESEMPI di TRIGGER

1) Garantire l’unicità dei valori di R.c
```sql
	CREATE OR REPLACE TRIGGER Trigger_Unique_R_c
	BEFORE INSERT ON R
	REFERENCING NEW AS NuovaTupla
	FOR EACH ROW
	WHEN (
		EXISTS (SELECT * FROM R WHERE R.c = NuovaTupla.c)
	)
	SIGNAL SQLSTATE '70000' ('Attributo c non è unico!')
```

2) Aggiorna la quantità residua di tutti i prodotti venduti inseriti in una nuova fattura
```sql
	CREATE TRIGGER UpdateQtaResidua
	AFTER INSERT ON Vendite
	REFERENCING NEW AS NuovaVendita
	FOR EACH ROW
	UPDATE Giacenze
	SET QtaResidua = Qtaresidua – NuovaVendita.Quantita
	WHERE CodProd = NuovaVendita.CodProd
```


# Viste 

Posso creare una tabella fittizia che si aggiornerà in automatico con le altre chiamata VISTA.
Con queste posso calcolare automaticamente valori come fossero variabili d'appoggio oppure nascondere parti di tabelle agli utenti ai quali non riguardano quei dati.

```sql
CREATE VIEW *nome*(*attr1*, *attr2*, ...) AS (
	*query (deve produrre lo stesso num di attributi che ho segnato sopra)*
)

WITH CHECK OPTION									-- (opzionale) permette di eseguire tutti i controlli della tabella originaria 
                                                                                        --se volessi provare ad inserire valori direttamente nella vista	
```


Dopodichè posso usarle tranquillamente in una qualsiasi query:

```sql
SELECT *
FROM *nomeVista*
WHERE ...

  --es. La sede che ha il massimo numero di impiegati
  -- con subquery
  SELECT I.Sede
  FROM Imp I
  GROUP BY I.Sede
  HAVING COUNT(*) >= ALL ( SELECT COUNT(*) FROM Imp I1 GROUP BY I1.Sede )

  -- con viste
  CREATE VIEW NumImp(Sede,Nimp) (
    AS SELECT Sede, COUNT(*)
    FROM Imp
    GROUP BY Sede
  )

  SELECT Sede
  FROM NumImp
  WHERE Nimp = (SELECT MAX(NImp) FROM NumImp)

```

Posso anche creare vere e proprie viste temporanee di appoggio, come fossero variabili, con la WITH.
La vista in questione va sempre accoppiata con la query in cui la uso, e verrà eliminata a fine esecuzione.

```sql
  --es. La sede che ha il massimo numero di impiegati
  WITH SediStip(Sede,TotStip) AS (
    SELECT Sede,SUM(Stipendio)
    FROM Imp
    GROUP BY Sede
  )
  SELECT Sede
  FROM SediStip
  WHERE TotStip = (SELECT MAX(NImp) FROM NumImp)
```
