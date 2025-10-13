//CHIRICHELLA DAVIDE 0001071414

import java.io.*;
import java.rmi.*;

public interface RMI_interfaceFile extends Remote {

	int elimina_parola(String fileName, String parola) throws RemoteException, FileNotFoundException;
	
	String[] lista_nomifile_soglia(String dirName, int soglia) throws RemoteException, FileNotFoundException;	

}