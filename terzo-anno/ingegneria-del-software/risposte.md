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

Un evento è un meccanismo che permette a una classe notificare altre entità "interessate" quando qualcosa di significativo accade in seguito
ad interazione con l'utente o cambiamenti di stato "interni" al programma.

Sono più potenti dei delegati in quanto hanno un sistema integrato di *registrazione* e *implementazione privata* 

Esso non fa altro che **incapsulare un delegato**, ma è più sicuro. Infatti il delegato, se pubblico, è accessibile direttamente da tutti.

All'evento, invece, possono solo essere aggiunti += o rimossi -= metodi che rispondono all'evento. 

Inoltre un evento espone solo i metodi add
e remove (+=, -=), ma non l'invocazione diretta (Invoke). Questo fa sì che solo la classe dichiarante possa scatenare l’evento, rendendo il tutto più sicuro


### Contenuto e comportamento

Il delegato va definito precedentemente, con i suoi due parametri:

- fonte che ha generato l'evento
- dati dedicati all'evento, se servono dati extra si usa un tipo che estende `EventArgs`

Se però non gestisce dei dati, è sufficiente usare la classe "default" `System.EventHandler`. 

## Funzionalità

- **Event sender**: la sorgente dell'evento. Non ha modo di conoscere receiver e handler.

- **Event receiver**: colui che si è precedentemente "iscritto" a un evento

- **Event handler**: codice per gestire un certo evento, necessario solo nei casi in cui in un evento possiedde dei dati

Essendo un delegato a tutti gli effetti, è possibile effettuare le operazioni di:

- `+=`: aggiunta di un delegato (handler) all'evento
- `-=`: sganciarsi dall'evento

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
sensata è riscrivere dacccapo quel particolare modulo "rigido", piuttosto che contro i principi di riusabilità del software

3. **Rigidità**: Si parla di rigidità quando una modifica di un elemento comporta la modifica di tutte le sue dipendenze
a cascata, rendendo quindi oneroso apportare delle modifiche al software, con la conseguente procrastinazione della cosa da parte
degli sviluppatori

4. **Viscosità**: Spesso le strategie ideate per apportare modifiche a un programma possono essere coerenti con l'idea originaria di design, 
ma possono altresì essere degli "hack", delle vie traverse che non preservano il design. La viscosità è la tendenza ad incoraggare la seconda
opzione. Le cause possono essere legate:

    - al design che, per "costituzione", rende difficile l'aggiunta di modifiche coerenti
    - all'ambiente, magari a causa di sistemi hardware inefficienti, sistemi di test lenti e VCS macchinosi
    
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

Il principio di sostituibilità di Liskov ha diverse formulazioni, una forte e una più debole:

- **Debole**: ogni istanza della superclasse (classe padre, detta anche classe "base"), deve essere associata all'istanza di una sottoclasse (figlia)

- **Forte**: chiunque utilizzi istanze della classe padre non deve percepire variazioni logiche rispetto all'uso delle istanze delle sue classi figlie

Più specificatamente, è opportuno definire i concetti di:

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



## CCP: Principio di Chiusura Comune

## CRP: Principio di Riutilizzo Comune

Per le relazioni tra package, ricordiamo invece:

## Principio delle dipendenze acicliche

## Principio delle dipendenze stabili

## Principio delle astrazioni stabili
