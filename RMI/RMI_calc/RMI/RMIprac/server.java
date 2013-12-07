import java.rmi.Naming;

public class server {
    public server() {
	try {
	    Calc c= new CalcImpl();
	    Naming.rebind("rmi://localhost:1099/CalcServer", c);
	} catch(Exception e) {
	    System.out.println("Exception" +e);
	}
    }

    public static void main(String args[]) {
	new server();
    }
}