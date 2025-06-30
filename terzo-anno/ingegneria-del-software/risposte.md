# Come viene implementata l’ereditarietà multipla?

Innanzitutto, con "ereditarietà" si intende la relazione tra due oggetti A e B in cui, se B eredita dalla classe A allora B è sottoclasse e A è superclasse.
Ricordiamo a tal scopo il principio di sostituibilità di Liskov, il quale afferma che una sottoclasse deve poter esibire tutti i comportamenti della superclasse,
così da renderla perfettamente sostituibile dall'esterno. La sottoclasse può esibire comportamente aggiunttivi rispetto alla superclasse o le stesse ma modificate
in modo trasparente rispetto all'esterno.

Si parla di ereditarietà multipla quando una sottoclasse eredita da due o più superclassi. Tuttavia, ciò non è consentito in Java e C#, in quanto è un processo che 
presenta alcune criticità. In particolare consideriamo la struttura a *diamante*, in cui una classe A possiede un metodo `doSomething()`, B e C sono classi figlie 
di A che ridefiniscono il metodo, e D a sua volta eredita sia da B che da C, è ambiguo capire quale implementazione specifica di doSomething D dovrà ereditare.

**Soluzione** in C# e Java: 
	1. Utilizzo di interfacce, le quali specificano solo la firma metodo e non la sua specifica implementazione
	2. Modello composizione e delega, funziona in questo modo
		- *composizione*: una classe è "costruita" usando altre classi come componenti
		- *delega*: un oggetto, invece di svolgere un compito "direttamente" delega a un altro oggetto
```java
class Motore  {
	void accendi() {
	    System.out.println("Motore acceso");
	}
    }
    class Auto {
	private Motore motore = new Motore(); // composizione, l'auto non È un motore

	void avvia() {
	    motore.accendi(); // delega a motore
	}
    }
```

# Si esegua una classificazione del polimorfismo secondo Cardelli-Wegner e si mostri l’implementazione del polimorfismo per inclusione.

Per polimorfismo si intende la capacità di una stessa entità di "apparire" in modo diverso in contesti differenti, o viceversa di apparire
allo stesso modo in contesti affini.
Il modello Cardelli-Wegner impone 2 "macro-categorie" di polimorfismo, a loro volta suddivise in due categorie

### Universale
Le entità possono assumere un numero illimitato di forme. 
    
#### Per inclusione
1. **Overriding** di:
    - Un metodo **astratto** della superclasse viene ridefinito in una sottoclasse (sicuro)
    - Un metodo **concreto** della superclasse viene ridefinito in una sottoclasse (meno sicuro)

2. Viene supportato il **binding dinamico** dei metodi, ovvero la possibilità di scoprire a runtime l'implementazione 
specifica del metodo che una classe dovrà esibre tramite VMT (virtual method table)

#### Parametrico

- La programmazione generica rispetto ai tipi considera la possibilità di specificare un **tipo** generico (T) come **parametro** di una classe. 
- Da ciò si comprende che i suoi **metodi** potranno opererare sui parametri generici
- Inotlre, da ogni classe generica si generano solo classi **indipendenti**, senza nessun rapporto di ereditarietà

```java
abstract class Animale {
    abstract void verso();
}

class Cane extends Animale {
    @Override
    void verso() {
        System.out.println("Bau");
    }
}

public class Main {
    public static void main(String[] args) {
        Animale a = new Cane(); // polimorfismo per inclusione
        a.verso(); // stampa "Bau", grazie alla VMT
    }
}
```
Funzionamento in questo esempio:
- Animale è una classe astratta con un  metodo astratto verso().
- Cane è un animale (lo estende) e fa l'override del metodo
- In main, a è dichiarato come Animale ma punta a un oggetto Cane.
- Quando chiamiamo a.verso(), viene invocata la versione ridefinita di Cane.

### Ad hoc
Le entità possono assumere un numero limitato di forme.

#### Overloading

- Consente la ridefinizone di **metodi/operatori** per ogni insieme di argomenti accettati
- Deve avvenire in fase di programmazione
            
#### Coercion
- Consente la **conversione implicita** del tipo di una variabile in un altro.
- La specifica delle conversioni possibili deve avvenire in fase di programmazione

# Procedimento di compilazione ed esecuzione del codice all’interno del framework .NET tramite il CLR.

Il CLR (Common Language Runtime) non è altro che un ambiente per eseguire runtime applicazioni .NET.

Il codice da esso gestito è detto **managed code**, ed è scritto tipicamente in C#. 

ùQuando scriviamo e lanciamo un'app in .NET, si passa da due fasi principali

1. **Compilazione**: il codice viene compilato in un linguaggio detto CIL (Common Intermediate Language), chiamato CIL ASSEMBLY.
Esso, insieme ad un **Manifest**, che identifica l'assembly (parametri come versione, tipo di assembly, req. di sicurezza), si trova
dentro un file `.dll` o un `.exe`

2. **Esecuzione**: il codice IL viene JIT (Just In Time), convertito in codice macchina nativo

CLR fornisce anche altre "garanzie" e servizi, quali

- **Garbage collector**: diversamente da COM, non c'è nessun reference counter, ma la distruzione dell'oggetto avviene quando 
esso non è referenziato da nessun altro. Ciò permette riferimenti circolari senza sprechi di memoria, ma il processo di distruzione
dell'oggetto non è più deterministico.

- Supporto all' **I/O** sui file

- Gestione delle **eccezioni** ereditando dalla classe System.Exception 
mediante blocchi *throw* (propagare un'eccezione),*catch* (catturare un'eccezione), *finally* (codice in uscita) 

# Differenza tra tipi valore e tipi riferimento in .NET

In CTS ogni classe eredita da System.Object, possiamo quindi fornire un modello di programmazione unificato. I tipi possono essere:
## Tipi
### Tipi valore

Sono dati (byte) opportunamente allocati sullo *stack*, o appartengono a *oggetti*, e possono essere:
    
    - **Primitivi**: boolean, float, double, Int32, char ...
    - **Custom**: definiti dall'utente

### Tipi riferimento

Sono indirizzi che rappresentano i riferimenti a uno specifico dato all'interno del "managed heap"

## Conversioni
### Boxing

Si definisce Boxing la conversione da un certo tipo "valore" a un tipo "riferimento" tramite cast up implicito

`double d = 3.3` -> `Object o = d` 

### Unboxing

Viceversa, si definisce unboxing la conversione di un certo tipo riferimento a un tipo valore tramite down cast esplicito

`double d = (double)o`

## Passaggio parametri

Può avvenire in tre modi distinti:

### In
Gli oggetti passati come argomento ai metodi vanno inizializzati prima

    - Valore: il metodo agisce su una copia
    
    - Riferimento: il metodo agisce su una copia del riferimento, non su quello originale

```java

```

### Out
Vanno inizializzati all'interno del metodo al quale sono passati come argomenti

```java

```

### In / Out
Gli oggetti passati come argomento ai metodi vanno inizializzati prima

    - Valore: il metodo agisce sul riferimento -> le modifiche hanno effetto su quello originale
    
    - Riferimento: le modifiche influenzano l'oggetto referenziato
    
```java

```

# Garbage collector in C#

### Scopo + Pro/Contro

Lo scopo del garbage collector è quello di deallocare risorse non più utilizzate da entità all'interno dell'applicazione, togliendo
dalle spalle del programmatore questa responsabilità.
Esso permette di risolvere problemi come:

- `Dangling pointer`: ovvero puntatori ad aree di memoria deallocate precedentemente ed eventualmente ora utilizzate da altri oggetti
- `Doppia deallocazione`: la stessa area viene deallocata 2 volte
- `Memory leak`: oggetti non più utilizzato che non viene deallocato

Le problematiche che possono sorgere sono relative a:

- Deallocazione non deterministica della memoria
- Spreco di risorse
- Incertezza di quando il garbage collector opererà

### Modalità

Un garbage collector può funzionare in 3 modalità diverse 

- `Reference Counting`: un contatore tiene traccia del numero di riferimenti ad esso, appena raggiunge lo 0 viene deallocato

Problemi: deve essere atomica, inefficace nei riferimenti ciclici

- `Escape analysis`: Gli oggetti vengono spostati dall'heap allo stack. A compile-time si stabilisce se un oggetti non può uscire dalla sua sub-routine 

- `Tracing`: (usata dal garbage collector in C#) Vengono liberate le aree di memoria occupate da oggetti irraggiungibili. Un oggetto è raggiungibile se:
    
    - è un oggetto **radice**, ovvero allocato all'inizio dell'esecuzione. Ogni radice punta a un oggetto di tipo riferimento sicuramente attivo, come:
        
        - variabili globali / campi statici
        - variabili locali / argomenti attuali
        - registri CPU
    
    - è **referenziato** a sua volta da un oggetto raggiungibile
    
da ciò, gli **oggetti vivi** sono quelli referenziati direttamente o indirettamente dalle radici, quelli **garbage** sono tutti gli altri.

Si nota come non la definizione di raggiungibilità dell'oggetto non è ottimale, in quanto ...
    
### Funzionamento

1. Il CLR riserva una regione contingua nello spazio di indirizzamento del progetto chiamata *managed heap*. 

2. Viene memorizzato l'indirizzo di partenza in un'area di memoria detta `NextObjPtr`

3. In caso venisse eseguita una `newobj`, quindi il CLR

4. Determina la dimensione dell'oggetto e gli aggiunge due campi da 32 o 64 bit:
    
    - Puntatore alla tabella dei metodi
    - SyncBlockIndex
    
3. Se, a partire dal `NextObjPtr` non c'è memoria disponibile
    
    - si chiama il GC
    - si lancia eccezione
    
5. I puntatori relativi all'oggetto creato vengono aggiornati

    - `thisObjPtr = NextObjPtr`
    - `NextObjPtr += sizeof(oggetto);`

6. Viene invocato il costruttore dell'oggetto

7. Viene restituito il riferimento all'oggetto

# Concetto di delegato in C#

I delegati sono oggetti che contengono riferimenti a metodi da invocare. Sono equivalenti ai **puntatori a funzioni** (functor) di C e C++.

### Contenuto e comportamento

- Viene definita soltanto la firma del metodo. Esso può inoltre contenere una *lista* di metodi, eseguiti in ordine, in modo sincrono,
l'uno dopo l'altro.

- Se viene passata una variabile by **reference (ref)**, ogni metodo nella lista vedrà la stessa variabile e può modificarla.

- Se un metodo ha un **valore di ritorno**, viene considerato solo quello dell’ultimo metodo della lista.

### Funzionalità di callback

- **Elaborazioni asincrone**: permette a un metodo di accettare un delegato come parametro così da chiamarlo in un momento successivo.
Appena esso termina, il chiamante viene avvertito.

- **Elaborazioni cooperative**: Ad esempio, un metodo svolge una parte del servizio e delega ad un altro metodo il resto (es. merge sort)

- **Gestione eventi**: C'è un generatore di eventi al quale un entità può "iscriversi", specificando quale metodo lo gestirà

### Esempio di utilizzo

- WORKER: deve effettuare delle attività
- BOSS: deve controllare l'attività dei suoi impiegati

Per comunicare al BOSS, il WORKER sfrutta un delegato che ha i riferimenti a tutte le sue attività

# Concetto di evento in C#


