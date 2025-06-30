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

1. Un metodo **astratto** della superclasse viene ridefinito in una sottoclasse tramite Overriding (sicuro)
2. Un metodo **concreto** della superclasse viene ridefinito in una sottoclasse tramite Overriding (meno sicuro)
3. Viene supportato il **binding dinamico** dei metodi, ovvero la possibilità di scoprire a runtime l'implementazione 
specifica del metodo che una classe dovrà esibre tramite VMT (virtual method table)

#### Parametrico

- La programmazione generica rispetto ai tipi considera la possibilità di specificare un **tipo** generico (T) come **parametro** di una classe. 
- Da ciò si comprende che i suoi **metodi** potranno opererare sui parametri generici
- Inotlre, da ogni classe generica si generano solo classi **indipendenti**, senza nessun rapporto di ereditarietà


### Ad hoc
Le entità possono assumere un numero limitato di forme.

#### Overloading

- Consente la ridefinizone di **metodi/operatori** per ogni insieme di argomenti accettati
- Deve avvenire in fase di programmazione
            
#### Coercion
- Consente la **conversione implicita** del tipo di una variabile in un altro.
- La specifica delle conversioni possibili deve avvenire in fase di programmazione


