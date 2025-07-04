
# Indice

## Modulo 1.1
- [ADT ed incapsulamento](#adt-ed-incapsulamento)
- [Come viene implementata l’ereditarietà multipla?](#come-viene-implementata-lereditarietà-multipla)
- [Si esegua una classificazione del polimorfismo secondo Cardelli-Wegner e si mostri l’implementazione del polimorfismo per inclusione.](#si-esegua-una-classificazione-del-polimorfismo-secondo-cardelli-wegner-e-si-mostri-limplementazione-del-polimorfismo-per-inclusione)
- [Differenze tra interfaccia e classe astratta](#differenze-tra-interfaccia-e-classe-astratta)
- [Ciclo di vita di un oggetto esemplificandone i passi utilizzando uno specifico linguaggio OO](#ciclo-di-vita-di-un-oggetto-esemplificandone-i-passi-utilizzando-uno-specifico-linguaggio-oo)

## Modulo 1.2
- [Tecnologia COM e Framework .NET](#tecnologia-com-e-framework-net)
- [Procedimento di compilazione ed esecuzione del codice all’interno del framework .NET tramite il CLR.](#procedimento-di-compilazione-ed-esecuzione-del-codice-allinterno-del-framework-net-tramite-il-clr)
- [Differenza tra tipi valore e tipi riferimento in .NET](#differenza-tra-tipi-valore-e-tipi-riferimento-in-net)
- [Garbage collector in C#](#garbage-collector-in-c)
- [Concetto di delegato in C#](#concetto-di-delegato-in-c)
- [Concetto di evento in C#](#concetto-di-evento-in-c)
- [Metaprogrammazione e riflessione in C#](#metaprogrammazione-e-riflessione-in-c)

## Modulo 1.3
- [Spiegare i quattro bad design (fragilità, immobilità, rigidità, viscosità)](#spiegare-i-quattro-bad-design-fragilità-immobilità-rigidità-viscosità)
- [Fattori di qualità di un buon software](#fattori-di-qualità-di-un-buon-software)
- [Principio di singola responsabilità con almeno un esempio](#principio-di-singola-responsabilità-con-almeno-un-esempio)
- [Principio di inversione delle dipendenze con almeno un esempio](#principio-di-inversione-delle-dipendenze-con-almeno-un-esempio)
- [Principio di segregazione delle interfacce con almeno un esempio](#principio-di-segregazione-delle-interfacce-con-almeno-un-esempio)
- [Principio aperto-chiuso con almeno un esempio](#principio-aperto/chiuso-con-almeno-un-esempio)
- [Principio di sostituibilità di Liskov con almeno un esempio](#principio-di-sostituibilità-di-liskov-con-almeno-un-esempio)
- [Principi per l’architettura dei package](#principi-per-larchitettura-dei-package)

## Modulo 1.4 (design pattern)
- [Pattern SINGLETON](#pattern-singleton)
- [Pattern OBSERVER](#pattern-observer)
- [Pattern FLYWEIGHT](#pattern-flyweight)
- [Pattern STRATEGY](#pattern-strategy)
- [Pattern ADAPTER](#pattern-adapter)
- [Pattern DECORATOR](#pattern-decorator)
- [Pattern COMPOSITE](#pattern-composite)
- [Pattern VISITOR](#pattern-visitor)
- [Pattern STATE](#pattern-state)
- [Pattern MODEL VIEW CONTROLLER](#pattern-model-view-controller)
- [Pattern MODEL VIEW PRESENTER](#pattern-model-view-presenter)
- [Pattern ABSTRACT FACTORY](#pattern-abstract-factory)

## Modulo 1.5
- [Modello LMU nei VCS con vantaggi e svantaggi](#modello-lmu-nei-vcs-con-vantaggi-e-svantaggi)
- [Modello CMM nei VCS con vantaggi e svantaggi](#modello-cmm-nei-vcs-con-vantaggi-e-svantaggi)

## Modulo 2
- [Spiegare il modello a cascata e le sue criticità.](#spiegare-il-modello-a-cascata-e-le-sue-criticità)
- [Spiegare il modello a cascata e il modello iterativo](#spiegare-il-modello-a-cascata-e-il-modello-iterativo)
- [Illustrare RUP](#illustrare-rup)
- [Tipologie di requisiti](#tipologie-di-requisiti)
- [Si illustri brevemente il ciclo di vita della valutazione del rischio](#si-illustri-brevemente-il-ciclo-di-vita-della-valutazione-del-rischio)
- [Principali categorie di requisiti per la sicurezza](#principali-categorie-di-requisiti-per-la-sicurezza)
- [Linee guida di progettazione nella sicurezza](#linee-guida-di-progettazione-nella-sicurezza)
- [White box e black box testing](#white-box-e-black-box-testing)
- [Capacità di sopravvivenza del sistema](#capacità-di-sopravvivenza-del-sistema)

---

# ADT ed incapsulamento

È un modello matematico per strutture dati che permette di definire:

**COSA** fa un certo tipo di dato senza specificare il **COME**, quindi quali **operazioni** e che **comportamento** avranno (utile per astrazione, modularità e riusabilità)

Per definirlo, serve:

- **interfaccia** pubblica, che specifica metodi pubblici applicabili a oggetti di quel tipo
- **implementazione** privata, con campi privati e metodi pubblici e privati

### Incapsulamento

O information hiding, significa nascondere agli utilizzatori finali i dettagli sulla struttura e il funzionamento interno, nascondendo scelte progettuali.

# Come viene implementata l’ereditarietà multipla?

Innanzitutto, con "ereditarietà" si intende la relazione tra due oggetti A e B in cui, se B eredita dalla classe A allora B è sottoclasse e A è superclasse.

Ricordiamo a tal scopo il principio di sostituibilità di Liskov, il quale afferma che una sottoclasse deve poter esibire tutti i comportamenti della superclasse,
così da renderla perfettamente sostituibile dall'esterno. La sottoclasse può esibire comportamente aggiunttivi rispetto alla superclasse o le stesse ma modificate
in modo trasparente rispetto all'esterno.

Si parla di ereditarietà multipla quando una sottoclasse eredita da due o più superclassi. Tuttavia, ciò non è consentito in Java e C#, in quanto è un processo che 
presenta alcune criticità.

In particolare consideriamo la struttura a *diamante*, in cui una classe A possiede un metodo `doSomething()`, B e C sono classi figlie 
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
- Inoltre, da ogni classe generica si generano solo classi **indipendenti**, senza nessun rapporto di ereditarietà

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

# Differenze tra interfaccia e classe astratta

## Interfaccia
#### SCOPO

Descrive una **funzionalità semplice** che può essere implementata da classi **eterogenee**. È come un "procotollo" da rispettare per le classi che lo utilizzano.

Esempio: tutte le classi che implementano l'interfaccia ICloneable sono clonabili, e possono essere classi di qualsiasi natura

#### STRUTTURA

Un insieme di metodi senza alcuna implementazione, che devono necessariamente essere definiti da tutte le classi che implementano l'interfaccia

Nessuno stato interno

Non c'è possibilità di usare metodi statici

Deve essere stabile (come dettato dall'OCP)

#### RELAZIONI con altre classi

Può estendere 0+ interfacce

## Classe astratta

#### SCOPO

Può descrivere funzionalità **anche complesse**, comune ad un insieme di oggetti **omogenei**. Può inoltre fornire anche implementazioni di alcuni metodi.

Esempio: la classe astratta Enum fornisce metodi comuni a tutti gli enumerativi.

#### STRUTTURA

I metodi possono avere o meno implementazione. Nel primo caso, può eventualmente essere ridefinita dalle classi che la estendono

Possibilità di avere dello stato interno

C'è possibilità di usare metodi statici

È aperta alle modifiche

#### RELAZIONI con altre classi

Può ereditare da 0+ interfacce e 0+ classi (minimo 1 se esiste una classe radice del sistema, *es. Object*, massimo 1 se non è consentita ereditarietà multipla)

Se vieene aggiunto un metodo, si può fornire un'implementazione di default per non farlo definire a tutte le classi concrete 

# Ciclo di vita di un oggetto esemplificandone i passi utilizzando uno specifico linguaggio OO

Consideriamo il linguaggio Java su JVM.

## INIZIO PROGRAMMA
la JVM alloca un area di memoria continua, detta **managed heap**, dove poi conservare gli oggetti allocati a runtime (la quale può crescere a runtime)

`NextObjPtr` = puntatore al primo indirizzo libero del managed heap

## NASCITA OGGETTO

new Oggetto ->
    
1. Calcola la dimensione in memoria che l'oggetto occuperebbe, analizzando tutti i campi . 
2. Controlla che nel managed heap ci sia abbastanza spazio. Esiti:
    - Positivo: GC
    - Negativo: OutOfMemoryException
3. `ThisObjPtr` = `NextObjPtr`; `NextObjPtr` = `sizeof(obj)` 
4. Invoca il costruttore della classe specificata. `(this = thisObjPtr)`;
5. Restituisce al chiamante della new il riferimento all'area di memoria.

Dopo questi passaggi l'oggetto viene utilizzato dal chiamante, e rimane in memoria finchè necessario. 

## MORTE OGGETTO 

Quando l'oggetto non è più "necessario" (in base alla **strategia di liberazione della memoria** del GC) la JVM procede a:

1.  Chiamare il metodo `finalize()` dell'oggetto (NON PIU CHIAMABILE DIRETTAMENTE).

2. Marcare lo spazio di memoria una volta preso dall'oggetto come di nuovo disponibile, così da permetterne l'utilizzo da parte di altri oggetti.

Le strategie per marcare un oggetto come "non necessario" sono molte. Ne analizziamo due:

### Reference counting

Utilizzato per esempio dal sistema COM, in cui a fianco dell'oggetto viene conservato il numero di puntatori attualmente attivi verso l'oggetto. 

### Tracing
Due fasi:

1. **marcatura**: oggetti raggiungibili sono:

    - oggetti con riferimenti sullo stack attuale
    - oggetti con riferimenti globali
    - riferimenti su registri CPU 
    
Si procede quindi alla marcatura ricorsiva di tutti i riferimenti che fanno parte degli oggetti radice e di quelli già marcati, saltando quelli già marcati precedentemente

2. **liberazione**

Gli oggetti presenti nel managed heap che non sono stati marcati durante la prima fase vengono finalizzati e ne viene liberata la memoria

# Tecnologia COM e Framework .NET

## COM

È un sistema orientato agli oggetti per produrre componenti software binari.

Non è un linguaggio, ma uno **standard**, specifica i requisiti di programmazione che permettono agli oggetti COM di interagire con altri oggetti

Tiene traccia della vita di un oggetto tramite **reference counting**. Ogni oggetto mantiene traccia di tutti gli altri oggetti che lo referenziano tramite questo contatore. Appena arriva a 0 l'oggetto stesso diventa responsabile della sua deallocazione

Ha una **limitazione**: la posizione di ogni componente è salvata nel registro Windows, quindi non è possibile avere due versioni dello stesso componente -> problema nelle dipendenze che usano versioni precedenti

## .NET

È un **ambiente di esecuzione** + **libreria di classi** che semplifica lo sviluppo e il deployment. 

È INTEGRATO con COM, ma INDIPENDENTE. Composto dai seguenti elementi:

- `IL`: linguaggio intermedio, il compilatore .NET traduce il codice di alto livello (di solito C#) in questo linguaggio intermedio (.exe o dll) e poi, tramite un compilatore JIT, lo converte in codice macchina

- `CLR` Common Language Runtime, è l'ambiente di esecuzione runtime per le applicazioni .NET, il cui codice eseguito è detto **managed code** (codice gestito)

- `CTS` Common Type System, sono i tipi di dato supportati da .NET (strutture dati, tipi primitivi, enumerativi, delegati), fortemente tipizzati. 

È permessa ereditarietà singola (di estensione) e multipla (di interfaccia)

l’invocazione dei metodi virtuali viene risolta a run-time (**late binding**)

Tutto viene ereditato dalla classe radice **Object**. Possibilità di fare boxing e unboxing 

- `CLS` Common Language Specification, regole che i linguaggi devono seguire per essere interoperabili 
 
 - identificatori (case sensivity, keyword)
 - costruzione oggetti (denominazione, proprietà...)

# Procedimento di compilazione ed esecuzione del codice all’interno del framework .NET tramite il CLR.

Il CLR (Common Language Runtime) non è altro che un ambiente per eseguire runtime applicazioni .NET.

Il codice da esso gestito è detto **managed code**, ed è scritto tipicamente in C#. 

Quando scriviamo e lanciamo un'app in .NET, si passa da due fasi principali

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

### Out (out)
Vanno inizializzati all'interno del metodo al quale sono passati come argomenti.

Viene passato per **riferimento** e le modifiche del valore dell’argomento (l’inizializzazione è obbligatoria) hanno **effetto sul chiamante**

### In / Out (ref)
Gli oggetti passati come argomento ai metodi vanno inizializzati prima

    - Valore: il metodo agisce sul riferimento -> le modifiche hanno effetto su quello originale
    
    - Riferimento: le modifiche influenzano l'oggetto referenziato
    

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

- ` this = thisObjPtr`

7. Viene restituito il riferimento all'oggetto

# Concetto di delegato in C#

I delegati sono oggetti che contengono riferimenti a metodi da invocare. Sono equivalenti ai **puntatori a funzioni** (functor) di C e C++.

### Contenuto e comportamento

- Viene definita soltanto la firma del metodo. Esso può inoltre contenere una *lista* di metodi, eseguiti in ordine, in modo sincrono,
l'uno dopo l'altro.

- Se viene passata una variabile by **reference (ref)**, ogni metodo nella lista vedrà la stessa variabile e può modificarla.

- Se un metodo ha un **valore di ritorno**, viene considerato solo quello dell’ultimo metodo della lista.

### Funzionalità

- **Elaborazioni asincrone**: permette a un metodo di accettare un delegato come parametro così da chiamarlo in un momento successivo.
Appena esso termina, il chiamante viene avvertito.

- **Elaborazioni cooperative**: Ad esempio, un metodo svolge una parte del servizio e delega ad un altro metodo il resto (es. merge sort)

- **Gestione eventi**: C'è un generatore di eventi al quale un entità può "iscriversi", specificando quale metodo lo gestirà

### Esempio di utilizzo

- WORKER: deve effettuare delle attività
- BOSS: deve controllare l'attività dei suoi impiegati

Per comunicare al BOSS, il WORKER sfrutta un delegato che ha i riferimenti a tutte le sue attività

# Concetto di evento in C#

Un evento è un meccanismo che permette a una classe notificare altre entità "interessate" quando qualcosa di significativo accade in seguito ad interazione con l'utente o cambiamenti di stato "interni" al programma.

I **DELEGATI** usavano campi pubblici per la registrazione, ma questa soluzione offre troppo accesso: 

- un cliente può sovrascrivere dei target precedentemente registrati
- li può invocare

Sono più potenti dei delegati in quanto hanno un sistema integrato di *registrazione* (pubblica) e campi delegati con *implementazione privata* 

Esso non fa altro che **incapsulare un delegato**, ma è più sicuro. Infatti il delegato, se pubblico, è accessibile direttamente da tutti.

All'evento, invece, possono solo essere aggiunti += o rimossi -= metodi che rispondono all'evento. 

Inoltre un evento espone solo i metodi add
e remove (+=, -=), ma non l'invocazione diretta (Invoke). Questo fa sì che solo la classe dichiarante possa scatenare l’evento, rendendo il tutto più sicuro


### Contenuto e comportamento

Il delegato va definito precedentemente, con i suoi due parametri:

- fonte che ha generato l'evento
- dati dedicati all'evento, se servono dati extra si usa un tipo che estende `EventArgs`

Se però non gestisce dei dati, basta utilizzare il delegato presente nella classe "default" `System.EventHandler`. 

## Funzionalità

- **Event sender**: la sorgente dell'evento. Non ha modo di conoscere receiver e handler.

- **Event receiver**: colui che si è precedentemente "iscritto" a un evento

- **Event handler**: codice per gestire un certo evento, necessario solo nei casi in cui in un evento possiedde dei dati

Essendo un delegato a tutti gli effetti, è possibile effettuare le operazioni di:

- `+=`: aggiunta di un delegato (handler) all'evento
- `-=`: sganciarsi dall'evento

Quindi un cliente può **aggiungere e rimuovere handler** per un evento 

ma non può ottenere o modificare in nessun altro modo l’elenco sottostante dei gestori di eventi

Per ricevere notifiche dall'evento, il cliente deve definire un metodo `EventHandler`

### Esempio
```java
public class Timer
{
    // Evento (incapsula un delegato di tipo EventHandler)
    public event EventHandler Tick;

    public void EseguiTick()
    {
        Console.WriteLine("Timer: scateno l'evento Tick!");
        Tick?.Invoke(this, EventArgs.Empty);
    }
}

public class Allarme
{
    public void RispondiAlTick(object sender, EventArgs e)
    {
        Console.WriteLine("Allarme: ricevuto il tick!");
    }
}

// -------------------------------------------------

Timer t = new Timer();
Allarme a = new Allarme();

// Registrazione del gestore (event handler) all'evento
t.Tick += a.RispondiAlTick;

// Scatenamento evento
t.EseguiTick();

```

# Metaprogrammazione e riflessione in C#

Con metaprogrammazione si intende un sistema che ha accesso a informazioni sul sistema stesso. 

A tal fine, si utilizza la "riflessione", la quale viene effettuata implementando la classe `System.Reflection`. Essa sfrutta i **metadati** (dati che 
descrivono altri dati), definiti da IDL

### Classi importanti

- `Type`: tutti gli oggetti sono istanze di tipi, e ogni tipo è un'istanza di type. Essi soono recuperabili con el.GetType()
    
- `Module`: 
- `Assembly`

Essa viene utilizzata per:

    - esaminare i dettagli di un assembly: 
    
        `Assembly.Load(...)` restituisce un oggetto Assembly, 
        
        `Assembly.GetModules(...)` restituisce un array di oggetti Module;
        
        `Module.GetTypes(...)` restitusice un array di Type.
    
    
    - istanziare oggetti e chiamare metodi a runtime
    
        `Activator.CreateInstance(type, ...)` invoca il costruttore specificato, è equivalente all’operazione new.
        
        `methodInfo.Invoke(...)` invoca i metodi;
        
        `propertyInfo.GetValue(...)/.SetValue(...)` invocano getter e setter.
    
    - creare, compilare ed eseguire assembly dove necessario
    
    
    - aggiungere informazioni ai metadati utilizzando attributi personalizzati, ovvero classi
    visibili via riflessione che derivano da System.Attribute e che possono contenere proprietà e metodi.
    
    Per creare attributi personalizzati occorre:
    
    1. dichiarare la classe dell’attributo;
    
    2. dichiarare i costruttori;
    
    3. dichiarare le proprietà;
    
    4. opzionalmente applicare AttributeUsageAttribute, che specifica alcune caratteristiche della classe,
    ovvero a quali elementi l’attributo è applicabile, quando l’attributo può essere ereditato e quando
    possono esistere molteplici istanze di un attributo.
    
    - Scrivere il codice IL necessario per creare e compilare un
    assembly che potrà essere chiamato direttamente dal programma che lo ha creato, e che potrà essere archiviato
    su disco in modo che altri programmi possano utiizzarl tramite la classe `System.Reflection.Emit`

# Spiegare i quattro bad design (fragilità, immobilità, rigidità, viscosità)

Un software è un prodotto che deve stare a certi standard di economicità, manutenibilità, affidabilità ed efficienza.

I "bad design" sono gli ostacoli che impediscono a un software di essere definito di qualità, e le cause possono essere
di natura eterogenea, legata ai progettisti, all'obsolescenza, all'esterno o alle crescenti modifiche:

1. **Fragilità**: Un software è fragile quando ogni minimo cambiamento alla struttura rischia di compromettere parti
di codice ad esso collegate (le dipendenze), talvolta anche in modo imprevedibile. Ciò rende molto oneroso il lavoro 
dello sviluppatore a causa del rischio di guasto che porta con sè una modifica

2. **Immobilità**: Un software immobile è tipicamente poco modulare, i componenti non sono facilmente riutilizzabili per scopi affini, in
quanto risultano troppo accoppiati con altre parti del sistema. Quindi, per uno sviluppatore, spesso l'idea più
sensata è riscrivere dacccapo quel particolare modulo "rigido", rendendolo quindi inutile al di fuori del proprio "recinto", contro i principi di riusabilità del software

3. **Rigidità**: Si parla di rigidità quando una modifica di un elemento comporta la modifica di tutte le sue dipendenze
a cascata, rendendo quindi oneroso apportare delle modifiche al software, con la conseguente procrastinazione della cosa da parte
degli sviluppatori

4. **Viscosità**: Spesso le strategie ideate per apportare modifiche a un programma possono essere coerenti con l'idea originaria di design, 
ma possono altresì essere degli "hack", delle vie traverse che non preservano il design. La viscosità è la tendenza ad incoraggare la seconda
opzione. Le cause possono essere legate:

    - al design che, per "costituzione", rende difficile l'aggiunta di modifiche coerenti
    - all'ambiente, magari a causa di sistemi hardware inefficienti, sistemi di test lenti e VCS macchinosi
    
# Fattori di qualità di un buon software

- **correttezza**: adempie ai suoi compiti correttamente

- **robustezza**: si comporta bene anche in situazioni anomale o impreviste, non crasha

- **affidabilità**: i sistemi / persone che dipendono dall'architettura riescono a farci pienamente affidamento

- **estendibilità**: il design permette di aggiungere facilmente modifiche non previste

- **riusabilità**: utilizzabile da altri programmi facilmente, ben integrabile

- **facilità d'uso**: si spiega da solo

- **efficienza**: buon uso delle tecnologie

- **verificabilià**: si sottopone bene ai test

- **portabilità**: si adatta alle varie piattaforme
    
# Principio di singola responsabilità con almeno un esempio

La "responsabilità" non è altro che un motivo che una classe ha per cambiare. Ogni classe dovrebbe avere un solo motivo per cambiare.

Il principio di singola responsabilità afferma che tutte le classi e i moduli dovrebbero essere sviluppate in modo da svolgere un'unica 
funzionalità generale, e che tutti i servizi da essi offerti devono contribuire unicamente ad adempiere quella specifica responsabilità

In sostanza è opportuno realizzare entità indipendenti tra loro che eseguano compiti semplici

### Esempio:

Classe `StampanteMultifunzione`, che può Scansionare foto, Stampare documenti

Se cambia il modo in cui si stampa, devo modificare la stessa classe anche se la scansione e l'invio email non c'entrano nulla

Divido le responsabilità in tre entità:

`Stampante` si occupa solo della stampa

`Scanner` si occupa solo della scansione

Ora ogni classe ha una singola responsabilità, ed è facile da modificare, testare o riutilizzare indipendentemente dalle altre.

# Principio di inversione delle dipendenze con almeno un esempio

Esso prevede che i moduli di alto livello (*utilizzatori*) non dipendano mai dai servizi di basso livello (*fornitori*), ma piuttosto che entrambi
dipendano da un "muro" di astrazioni che li disaccoppia.

I moduli di *basso livello* contengono infatti il codice pesante, la logica di business, che andrebbe isolata.

Utilizzare *astrazioni* stabili con codice permette di:

    - introdurre una separazione netta tra moduli astratti e concreti 
    
    - evitare rigidità (per ogni modifca bisognerebbe agire su molti moduli)
    
    - evitare fragilità (con le modifiche si andrebbe a toccare roba rischiosa)
    
    - evitare immobilità (impossibilità di riutilizzare il codice)

    - avere cambiamenti che non si propagano più (*Design for change*)
    
    - rendere i singoli modi riutilizzabili (*Design for reuse*)

### Esempio:

# Principio di segregazione delle interfacce con almeno un esempio

Il cliente non deve dipendere da metodi che non usa, ma definire solo quelli necessari al suo funzionamento.

Ha più senso che esso implementi *più interfacce* specifiche anzichè una *fat interface*

Se non si facesse, sarebbe difficile manutenere il sistema a causa di questo "monolite" che definisce tutti i metodi

### Esempio:

Immagina un’interfaccia `MacchinaUfficio` con metodi:

```
Stampa() -> meglio avere Istampante
Scansiona() -> meglio avere IScanner
Fax() -> meglio avere IFax
```
Ora, un oggetto `StampanteBase` che sa solo stampare, è costretto a implementare anche Scansiona() e Fax(), che non gli servono → interfaccia troppo grande.

# Principio aperto/chiuso con almeno un esempio

L'open closed principle prevede che un sistema sia aperto alle estensioni software, ma sia chiuso alle modifiche. Per fare ciò, è necessario
avere un riferimento "stabile" e immutabile, come classi astratte e interfacce, opportunamente implementate.

Nel caso in cui si voglia modificare il codice basterà creare una nuova classe concreta che implementa le astrazioni.

Questo permetterà di non toccare moduli scritti precedentemente e scrivere le estensioni in un contesto sicuro.

Per farlo si occorre all'ereditarietà:

- **Di interfaccia**: si crea un'interfaccia con **metodi virtuali**. L'interfaccia sarà CHIUSA ALLE MODIFICHE, le sue implementazioni APERTE ALLE ESTENSIONI

- **Dell'implementazione**: Si creano nuove **sottoclassi** che estendono la classe base, evitando ripetizioni nelle sottoclassi

### Esempio



# Principio di sostituibilità di Liskov con almeno un esempio

Il principio di sostituibilità di Liskov afferma che un cliente che usa istanze di una certa classe A deve poter usare istanze di una qualsiasi sottoclasse di A senza accorgersi della differenza

formalmente, le formulazioni sono due, una forte e una più debole:

- **Debole**: ogni istanza della superclasse (classe padre, detta anche classe "base"), deve essere associata all'istanza di una sottoclasse (figlia)

- **Forte**: chiunque utilizzi istanze della classe padre non deve percepire variazioni logiche rispetto all'uso delle istanze delle sue classi figlie

### Design by contract

La principale causa di violazioni al principio di Liskov è data dalla ridefinizione di metodi virtuali nelle classi virtuali;

la chiave per evitare queste violazioni risiede nel design by contract. Nel design by contract ogni metodo ha:


- **Precondizioni**: sono i requisiti che un chiamante deve rispettare affinchè il metodo invocato possa essere eseguito correttamente.

    Esse, in ogni metodo reimplementato da una sottoclasse, devono essere uguali o meno restrittive.
    
- **Postcondizioni**: sono i requisiti che il chiamato deve soddisfare in caso di esecuzione corretta.

    Esse, in ogni metodo reimplementato da una sottoclasse, devono essere uguali o più restrittive.
    
- **Semantica**: deve essere conservata dalle classe figlie

- **Vincoli**: non è possibile aggiungerne altri rispetto alla superclasse

### Esempio

Hai una classe `Animale` con il metodo `Muovi()`.

Crei `Cane : Animale`, e fin qui tutto ok.

Poi crei `Pesce : Animale`, ma forzi `Pesce` a implementare `Muovi()` come se potesse camminare ! comportamento errato !.

Soluzione: Progetti una gerarchia più adatta:

```
Animale
     AnimaleTerrestre : Muovi()
    - AnimaleAcquatico : Nuota()
```

Ora ogni sottoclasse fa ciò che ha senso, e può sostituire il suo tipo padre senza effetti collaterali.

# Principi per l’architettura dei package

## REP: Principio di Equivalenza Rilascio

Ogni package che viene rilasciato al pubblico dovrebbe essere opportunamente **manutenuto** e gestito da un **sistema di rilascio** , e i clienti non dovrebbero utilizzare quelli senza manutenzione 

> anche le edizioni precedenti vanno manutenute e versionate

Occorre raggruppare classi in package (che sono l'**unità di rilascio** in Java) così da garantire il riutilizzo di una o più classi

## CCP: Principio di Chiusura Comune

Rilasciare un package significa garantire che tutte le classi in esso contenute siano opportunamente testate 

L'uso dei package dovrebbe essere ridotto al minimo. Ognuno di essi deve contenere tutte le classi che vengono modificate insieme, così da rendere facile modifica di ognuna di esse riducendo al **minimo il numero di package modificati in ogni ciclo di rilascio**

Incita l'utilizzo di PACKAGE GRANDI, utile solo in fase iniziale per "semplificare la vita" ai manutentori, poi sarà necessario un refactoring

## CRP: Principio di Riutilizzo Comune

Una dipendenza da un package, implica una dipendenza da tutto ciò che è nel package.

Ad ogni rilascio, gli utilizzatori del package devono controllare la compatibilità con tutto ciò che è in esso, anche se non lo usano

Incita l'utilizzo di PACKAGE PICCOLI che raggruppano solo le classi che vengono riutilizzate insieme

> Per le relazioni tra package, ricordiamo invece:

## Principio delle dipendenze acicliche

## Principio delle dipendenze stabili

## Principio delle astrazioni stabili

# Pattern SINGLETON

Il pattern singleton è un pattern di tipo **creazionale** in cui si vuole garantire che una classe abbia 

- un'**unica istanza** controllata
- un punto di accesso globale a tale istanza 
- intercettare tutte le richieste di creazione garantendo che non ce ne siano altre

Esso è composto da un **costruttore vuoto privato** e un unico metodo **statico** `getInstance()` che restituisce l'istanza "protetta", creandola solo se non c'è già

Una classe con soli membri statici non è un'alternativa valida, perchè 

- non permette di creare istanze personalizzate in base al contesto
- non permette un numero di interfacce arbitrarie

## Esempio

```java
public class Singleton {
    private static Singleton istanzaUnica;

    // Costruttore privato
    private Singleton() {}

    public static Singleton getInstance() {
        if (istanzaUnica == null) {
            istanzaUnica = new Singleton();
        }
        return istanzaUnica;
    }

    public void doSomething() {
    }
}
```

# Pattern OBSERVER 

È un pattern di tipo **comportamentale** che prevede la presenza di un **Subject** che, in base a certe condizioni, notifica degli **Observer** interessati a conscerne i cambiamenti

- `Subject`:

    `Attach(observer)`, `Detach(observer)`: rispettivamente i metodi per registrarsi e deregistrarsi dal subject che mantiene un riferimento agli observer da notificare
    
    `Notify()`: chiama il metodo `update()`  di tutti gli observer da notificare

- `Observer`: Metodo `update()`, la logica di business specifica dopo aver ricevuto la notifica da un evento

Esso può essere implementato in modi diversi:

- **class based**: Ogni subject ha il riferimento diretto agli observer

- **interface based**: Ogni subject ha il riferimento all'interfacca che i diversi Observer concreti implementeranno (ci piace, disaccoppiamento tramite interfaccia)

- **delegate based**: Ogni subject ha un delegato pubblico, in modo tale che gli observer possano registrarsi al delegato ed essere notificati da lì indirettamente

- **event based**: Un event si occupa di effettuare il `detach` degli observer

## Esempio

Dispositivi IoT 

# Patter FLYWEIGHT

Il pattern Flyweight è un pattern **strutturale** viene applicato quando si gestiscono oggetti leggeri (a granularità molto fine) e per i quali non si vogliono sprecare risorse
istanziando ogni volta lo stesso oggetto, ma comunque si vuole poterlo "personalizzare" in base all'utilizzo

Un **flyweight**  è un oggetto condiviso utilizzato da più *client* simultaneamente, la cui condivisione è garantita da un **FlyweightFactory**.

Esso, benchè condiviso, deve essere **indistinguibile** da un oggetto non condiviso.

Esso può avere due stati:

    - **stato intrinseco**: la parte condivisibile e costante, è interna all'oggetto e visualizzata da tutti i client
    
    - **stato estrinseco**: la parte variabile, viene passata esternamente
    
## Esempio

Carattere

# Pattern STRATEGY

È un pattern di tipo **comportamentale**. Esso viene utilizzato quando si ha una famiglia di algoritmi che vengono utilizzati per svolgere la stessa funzionalità

Per perseguire questo scopo si definisce un'**interfaccia** che espone il metodo, e poi si creano le rispettive **classi concrete** che implementano il metodo secondo il proprio algoritmo specifico

Un cliente quindi potrà dipendere unicamente dall'interfaccia, senza fare assunzioni sulla "strategia" specifica verrà adottata per il compito

## Esempio

Interfaccia: `ISortStrategy` che espone il metodo `int[] sort(int[])`

Classi concrete specifiche `BubbleSortStrategy` [...]

Il `Cliente` farà riferimento ad un oggetto `IsortStrategy`

# Pattern ADAPTER

È un pattern **strutturale** che serve a far comunicare due classi incompatibili tra di loro.

Ipotizziamo un *client* che utilizza un'interfaccia `Target` già definita che espone un **metodo**, il quale però è definito in una classe `Adaptee` incompatibile con la suddetta interfaccia. 

Si utilizza una classe `Adapter` il cui ruolo è

- Implementare l'interfaccia `Target`
- "Wrappare" il metodo incompatibile di `Adaptee`

## Esempio

Target: `interface Logger : void log(string)`
Adaptee: `class OldLogger : void writeLog(string)`
Adapter: `Adapter implements Logger : voig log(string){ OldLogger.writeLog(string) }`, prende il vecchio logger nel costruttore

# Pattern DECORATOR

È un pattern **strutturale** che serve per aggiungere dinamicamente proprietà agli oggetti.

Risulta più "potente" della semplice ereditarietà in quanto:

- La classe viene estesa a runtime, non a tempo di compilazione
- Il codice è più pulito, evita classi monolitiche o una gerarchia con troppi sottotipi

L'idea è quella di avere le seguenti entità

- un `Component`, interfaccia che definisce l'oggetto in questione. Esempio: `interface Bevanda`

- un `ConcreteComponent`, implementazioni concrete dell'interfaccia che vogliono essere "decorate". Esempio: `Caffe implements Bevanda`

- un `Decorator`, interfaccia conforme con quella del `Component`, che mantiene un riferimento. Esempio: `abstract class DecoratoreBevanda implements Bevanda`, contiene `protected Bevanda b` 

- un `ConcreteDecorator` che implementa il decorator. Esempio: `class Latte extends DecoratoreBevanda`

```java
Bevanda b = new Caffe(); // Caffè base
b = new Latte(b);        // Aggiungi latte
b = new Zucchero(b);     // Aggiungi zucchero
```

# Pattern COMPOSITE

È un pattern **strutturale** che permette di gestire delle strutture ad albero, trattando oggetti e gruppi di oggetti allo stesso modo.

Oggetti e Contenitori di oggetti verranno quindi acceduti dal Client allo stesso modo

- `Component` classe **astratta** che dichiara l'interfaccia e definisce **comportamenti comuni** tra oggetti e composizioni

    Contiene il **riferimento al genitore** e la relativa *gestione*

    > Alcune operazioni potrebbero essere prive di significato per le foglie, come Add() e Remove(),
    dovrebbero avere una realizzazione di default 

    Esempio: `FileSystemItem`, che definisce un metodo `stampaStat()`


- `Composite`: Oggetto composto che contiene altri component. Il contenitore dei figli deve essere un attributo di tipo **composite**,  come lista, mappa, etc...

    Esempio: `Cartella`, definisce metodi `add(FileSystemItem)` e `remove()`, e memorizza la lista di `FileSystemITem`.


- `Leaf`: oggetti che non possono avere figli

    Esempio: `File`

# Pattern VISITOR

È un pattern **comportamentale** che permette di implementare operazioni custom su delle classi senza andare a toccare il codice della classe stessa.

Esso è in linea con l'**open closed** principle (l'intero sistema consente di essere esteso con nuove operazioni, se rispettano un protocollo) e il **single responsibility** principle, ogni funzionalità / operazione è una classe apposita.

L'idea è che Oggetti diversi **accettano** un visitatore. Il visitatore decide **cosa** fare con ognuno. Gli oggetti non cambiano mai quando aggiungi nuove operazioni.

- `Visitor` classe astratta o interfaccia, dichiara il metodo `Visit(elementA)` per gli specifici elementi su cui esso potrà operare 

    > Esempio: `calcolaArea(Cerchio c), calcolaArea(Rettangolo r)`

- `ConcreteVisitor` implementazione

- `Element` dichiara il metodo `Accept(Visitor)`, permette di essere "esplorata" dal visitor per farci dei calcoli

    > Esempio: `accept(Visitor v)`, poi implementata come `{ v.visita(this) }`, saprà già cosa fare in base al tipo di this

- `ConcreteElement` 

- `ObjectStructure` è realizzata come **Composite** o come una collezione (array, lista, etc.) e deve contentire l’enumerazione dei suoi elementi ; per permettere di essere visitabile da Visitor, ObjectStructure deve implementare un’interfaccia apposita `Visitable`.

Utilizzo: 

```java
Forma f1 = new Cerchio(3);

FormaVisitor calcolaArea = new CalcolaArea();

f1.accept(calcolaArea);    // calcola area cerchio
```

# Pattern STATE

È un pattern **comportamentale** che localizza il comportamento specifico di uno stato, permettendo a un componente di cambiare comportamento a seconda del suo stato interno.

Le classi concrete contengono la logica di transizione da uno stato all’altro e il pattern permette anche di emulare
l’ereditarietà multipla

- `Context`: mantiene un riferimento allo stato corrente e lo delega

- `State`e`ConcreteState`: metodi comuni a tutti gli stati e le loro implementazioni

```java
interface State {
    void pressSwitch(Light context); // deve essere accesa o spenta
}

// Stato: Spento
class OffState implements State {
    public void pressSwitch(Light context) {
        System.out.println("Luce accesa!");
        context.setState(new OnState()); // logica di transizione da uno stato all'altro
    }
}

// Stato: Spento
class OnState implements State {
    public void pressSwitch(Light context) {
        System.out.println("Luce accesa!");
        context.setState(new OnState()); // logica i transizione da uno stato all'altro
    }
}

// Contesto: Lampadina
class Light {
    private State state;

    public Light() {
        state = new OffState(); // inizialmente spenta
    }

    public void setState(State state) {
        this.state = state;
    }

    public void pressSwitch() {
        state.pressSwitch(this);
    }
}
```

# Pattern MODEL VIEW CONTROLLER

Il pattern MVC è di tipo architetturale, e serve per introdurre una chiara separazione di ruoli tra componenti di basso livello (logica di business) e alto livello (presentazione), introducendo anche un elemento intermedio:

### Model

Modello dai dati, con operazioni di accesso e modifica. Generalmente sono degli oggetti **Observable** che notificano alla view il loro cambiamento di stato

### View

Logica di presentazione su un dispositivo di output. Sono degli oggetti **Observer** che si iscrivono ai dati del model volendo rilevarne i cambiamenti di stato. 

### Controller

Si occupa di prendere gli input dall'utente mappandole opportunamente in **comandi** che andranno a modificare view o model.

# Pattern MODEL VIEW PRESENTER

Simile al MVC, ma introduce ancora più separazione tra i ruoli dei singoli componenti. Si usano **più presenter** ognuno associato ad una particolare view.

### Model

Modello dai dati logicamente correlati. Generano un **evento** quando lo stato cambia. Gestiscono la **registrazione in forma anonima** degli oggetti interessati alla notifica dell'evento.

### View

Si **registra presso il presenter** e mappa i dati forniti dal presenter. 

### Presenter

Gestisce input dall'utente e mappa le azioni in comandi. Aggiorna la view.

# Pattern ABSTRACT FACTORY

È un design pattern **creazionale** che serve a creare famiglie di oggetti correlati fra loro.

L'obiettivo è separare la **creazione** degli oggetti dal loro **utilizzo**

Basta avere un' `Interfaccia` detta `AbstractFactory`, ad esempio `CarFactory : Motore creaMotore(), Telaio creaTelaio()` che "produce i pezzi". I factory concreti la implementeranno, ad esempio per l'auto elettrica oppure a benzina. `Auto` potrà prendere un `CarFactory` come parametro e creare motore e telaio. 

# Modello LMU nei VCS con vantaggi e svantaggi

Un VCS (Version Control System), permette avere pieno controllo dello sviluppo di un progetto, consentendo di tenere traccia del lavoro proprio e di quello in collaborazione con altri e avere pieno controllo delle versioni, potendo anche fare rollback

Il modello `Lock Modify Unlock` fa in modo che per ogni file del repository (la cartella remota dove sono memorizzati i dati correnti e passati del progetto) venga esplicitamente dichiarato se si sta modificando un file, così bloccandolo alla modifica di tutti gli altri. Terminate le modifiche, sarà nuovamente accessibile per la modifica.

### Problemi:

- **Falso senso di sicurezza**: se due sviluppatori modificano indipendentemente due file che "dipendono" l'uno dall'altro, comunque potrebbero esserci conflitti

- **Serializzazione inutile**: nella stragrande maggioranza dei casi, la modifica simultanea di un file non porta conflitti

- **Dimenticanze**: Se uno dimentica la "flag" su un file che ha terminato di modificare ci sono rallentamenti

### Quando conviene?

- Edit di file non modificabili simultaneamente / non unibili, come binari o immagini

# Modello CMM nei VCS con vantaggi e svantaggi

Il modelllo CMM `Copy, Modify, Merge`, consente di poteer modifcare i file in una repository senza nessun meccanismo di lock - unlock.
In particolare:

1. Check out: viene presa una copia dei file dal repository 
2. edit: vengono modificati i file
3. Check in: viene fatto un **merge** (unione) tra le modifiche dell'utente e quelle degli altri utenti. Questa operazione può avere esito:

    - POSITIVO: nessun conflitto tra i file
    - NEGATIVO: conflitti che vanno risolti a mano.

Questa, ovviamente, non è una garanzia di funzionamento dell'applicativo. 

### Vantaggi

- Possibilità di modificare un file in parallelo senza doversi aspettare a vicenda

- La risoluzione manuale dei conflitti è comunque meno onerosa rispetto al blocco, modifica, sblocco

- Conflitti rari

### Quando non conviene?

- File non unibili (unmergeable) come immagini o binari.

# Spiegare il modello a cascata e le sue criticità.

Il modello a cascata è un modello di sviluppo software che passa attraverso queste 7 fasi, ognuna delle quali va svolta in maniera esaustiva:

1. studio di fattibilità
2. analisi dei requisiti
3. analisi del problema
4. progettazione
5. implementazione
6. collaudo
7. manutenzione

Per rendere questo modello efficace c'è bisogno di definire:

- **Semilavorati**: È come una pipeline composta da documenti, codici, sistema che vengono passati alla fase successiva

- **Date**: le scadenze entro cui vanno prodotti i semilavorati, così da tracciare il progresso del lavoro (workflow)

### Quando è utile?

- Immobilità dei requisiti: ovvero si sanno chiaramente i req. iniziali dell'applicazione

- Immutabilità del progetto: progettare l’intero sistema prima di avere scritto codice risulta possibile

Spesso, è utile avere **forme limitate di retroazione** tra i livelli e un **throw away prototype**, dal quale poi verrà costruito il sistema reale rispettando il modello a cascata (COSTOSO)

### Svantaggi

- I requisiti cambiano nel tempo

- Il progetto spesso va revisionato

# Spiegare il modello a cascata e il modello iterativo

> Modello a cascata detto sopra

Il modello iterativo, invece, prevede dei passi che sono via via più specifici, aumentando di volta in volta il livello di dettaglio del sistema. Esempio *RUP*

# Illustrare RUP

È un modello di sviluppo software iterativo ed ibrido pensato per software di grandi dimensioni

## Prospettiva Dinamica

### Avvio 

delineare il business case, agenti **esterni** (a chi ci si rivolge) ed il **mercato**

### Elaborazione

Definisce l'architettura complessiva del sistema. È importante arrivare ad

- aver determinato almeno l'80% dei casi d'uso
- descrizione architettura iniziale
- sviluppo architettura
- architettura che copre casi d'uso principali eseguibile funzionante
- revisione business case 
- pianificazione progetto complessivo

### Costruzione

Progettazione, programmazione e collaudo del sistema. Alla fine di questa fase il sistema dovrebbe essere **funzionante** e la documentazione **pronta**

Le parti vengono sviluppate in **parallelo**, poi integrate fra di loro

### Transizione

dall'ambiente di sviluppo a quello di beta testing

## Prospettiva Statica

Si focalizza sulle attività di **PRODUZIONE DEL SOFTWARE** (workflow), di cui abbiamo

### 6 workflow principali

1. Modellazione attività aziendali: 
2. Requisiti:
3. Attività e progetto: viene creato un *modello di progetto*
4. Implementazione:
5. Test:
6. Rilascio:

### 3 di supporto

1. Gestione configurazione e modifiche: gestione dei *cambiamenti* del sistema
2. gestione del progetto: gestione dello *sviluppo* del sistema
3. Ambiente: strumenti adeguati agli sviluppatori

## Prospettiva Pratica

Sono le **BUONE PRASSI** da seguire nello sviluppo dei sistemi

1. Sviluppo ciclico del software: con scala di priorità
2. Gestione dei requisiti: documenta ogni scelta del cliente
3. Uso architetture a componenti: modularità
4. Modelli visivi: come UML
5. Verifica qualità del software: 
6. Controllo modifiche: tramite strumenti

# Tipologie di requisiti

I requisiti di un particolare applicativo software descrivono i servizi che esso deve fornire e i loro rispettivi vincoli. 

SOno di 3 tipi principali:

## Utente

Brevi, scritti in linguaggio naturale e ad alto livello. Specificano **vincoli** del sistema e **condizioni** attorno a cui opera.

## Di sistema

Uguali a prima ma più dettagliati:

### Funzionali

Elenca i servizi che il sistema deve fornire, come comportarsi in base a certi input, come comportarsi in specifiche situazioni, cosa il sistema non dovrebbe fare.

### Non funzionali

Robe più specifiche, come:

**requisiti del prodotto**: limitazioni alle proprietà del sistema

**requisiti organizzativi**: vincoli al processo di sviluppo

**requisiti esterni**: privacy, etica etc... possono andare in conflitto con altri (es. facilità d'uso)

### Di dominio

Indicano il funzionamento del sistema all'interno dello specifico dominio

# Si illustri brevemente il ciclo di vita della valutazione del rischio

Serve a bilanciare eventuali perdite dovute ad attacchi informatici andati a segno grazie a  lacune di sicurezza del prodotto software.

La valutazione del rischio è composta da 2 fasi:

## Valutazione preliminare del rischio:

Vengono determinati i **requisiti di sicurezza** dell'applicazione.

## Ciclo di vita della valutazione del rischio:

Essa avviene parallelamente al ciclo di vita dello sviluppo di un software, non è un optional.

1. **precondizioni**: aver capito quali sono le piattaforme in uso, in particolare il middleware e la strategia di sviluppo del sistema

2. **identificazione del bene**: risorse FISICHE e LOGICHE e le DIPENDENZE tra i due

3. **identificazione delle minacce**: cosa NON DEVE POTER ACCADERE nel sistema

# Principali categorie di requisiti per la sicurezza

Lo scopo è di definire quali comportamenti risultano inaccettabili per il sistema

### identificzazione

specificano se un sistema deve eseguire l'identificazione degli utenti

### autenticazione

modalità di autenticazione degli utenti

### autorizzazione

cosa un utente può / non può fare

### integrità

spiecificano i meccanismi per evitare corruzioni di dati

### immunità

meccanismi per garantire difese da malware

### scoperta delle intrusioni

self-explained

### non-ripudiazione

una delle due parti delle transazioni non può dire di non aevr partecipato

### riservatezza

delle informazioni

### controllo della protezione

utulizzo del sistema controllato e verificato

### protezione della manutenzione del sistema

se vengono rotti i meccanismi di protezione, come un'app può annullare modifiche?

# Linee guida di progettazione nella sicurezza

1. Redigere un documento esplicito che specifichi precisamente tutte le politiche di sicurezza, ma non COME applicarle (i meccanismi)

2. Evitare ogni singolo punto di fallimento che potrebbe dare criticità al sistema. Se fallisse, farlo in modo controllato

3. Adottare il principio del "Minimo privilegio", ovvero gli utenti di default dovrebbero avere solo i privilegi necessari

4. Deployment conttollato

5. Validazione e sanificazione di input per evitare BOF e SQLi

6. Bilanciare sempre sicurezza e usabilità

7. Garantire due principi

    - **ridondanza**: più versioni della stessa entità
    - **diversità**: tecnologie diverse per varie componenti
    
8. Organizzare le informazioni in "compartimenti" ai quali gli utenti possono accedere

9. Metodi adeguati per il rollback e ripristini in caso di errori

# White box e black box testing
1. **black box**, test a scatola chiusa, senza sapere il codice sorgente come farebbe un vero attaccante:

    - utile per test di performance, e di affidabilità del sistema
    - perdita di tempo per sicurezza

2. **white box**: consci del codice, revisione ad hoc del sistema
    
    - vulnerabilità
    - leggibilità e modularità del codice

# Capacità di sopravvivenza del sistema

Per capacità di sopravvivenza del sistema si intende l'abilità di quest'ultimo di riuscire ad erogare un servizio anche sotto attacco o con componenti danneggiate.

Esso non riguarda solo i singoli componenti, ma l'*intero sistema*. Risulta cruciale sopratutto perchè spesso beni economici / personali dipendono da esso.

A tale scopo è stato ideato il **Survivable Analysis System** che struttura la sopravvivenza di un sistema in base a 4 fasi, mosse da 3 principi:

- `Identificazione`: **individuare** problemi grazie a un sistema che riconosce eventuali attacchi e fallimenti, **valutandone** il danno.

- `Resistenza`: **respingere** attacchi

- `Ripristino`: **garantire** il funzionamento nonostante l'attacco e **ripristinare** i servizi dopo l'attacco

Le 4 fasi sono:

- **comprensione del sistema**: tutta l'architettura con le sue componenti va analizzata nel dettaglio per comprenderne tutti i servizi

- **identificazione servizi critici**: dopo aver analizzato l'architettura si identificano i servizi a rischio, con tutte le possibilità di attacco sia dirette che trasversali

- **simulazione attacchi**: simulando attachi, individuando i casi d'uso e componenti soggetti agli attacchi

- **analisi della sopravvivenza**: vedere se il sistema è riuscito bene a identificare un tentativo di attacco e a bloccarlo con successo, ed eventualmente a ripristinarsi in caso fossero stati sotto attacco
