RMI(Remote Method Invocation)
Name      : Kritika Rai
Roll No.  : 4345
___________________________________________________________________________

import java.rmi.Naming;

public class RMIServer {

    public RMIServer() {
        try {
            SetInterface s = new SetImplementation();
            Naming.rebind("rmi://localhost:1099/SetOperationsService", s);
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }

    public static void main(String args[]) {
        new RMIServer();
    }
}

___________________________________________________________________________