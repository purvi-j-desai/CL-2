					// Set Implementation

___________________________________________________________________________________

import java.lang.Integer;
import java.rmi.RemoteException;
import java.util.HashSet;
import java.util.Set;

public class SetImplementation extends
        java.rmi.server.UnicastRemoteObject
        implements SetInterface {

    protected SetImplementation() throws RemoteException {
        super();
    }

    public Set<Integer> union(Set<Integer> a, Set<Integer> b) 
					throws RemoteException {
        Set<Integer> unionSet = new HashSet<Integer>(a);
        unionSet.addAll(b);
        return unionSet;
    }

    public Set<Integer> difference(Set<Integer> a, Set<Integer> b) 
					throws RemoteException {
        Set<Integer> diffSet = new HashSet<Integer>(a);
        diffSet.removeAll(b);
        return diffSet;
    }

    public Set<Integer> intersection(Set<Integer> a, Set<Integer> b) 
					throws RemoteException {
        Set<Integer> interSet = new HashSet<Integer>(a);
        interSet.retainAll(b);
        return interSet;
    }
}



_____________________________________________________________________________