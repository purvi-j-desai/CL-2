					// Set Interface


________________________________________________________________________

import java.lang.Integer;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Set;

public interface SetInterface extends Remote{
    public Set<Integer> union(Set<Integer> a, Set<Integer> b) 
					throws RemoteException;

    public Set<Integer> intersection(Set<Integer> a, Set<Integer> b) 
					throws RemoteException;

    public Set<Integer> difference(Set<Integer> a, Set<Integer> b) 
					throws RemoteException;
}



________________________________________________________________________
