import java.io.*;
import java.lang.Integer;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.net.MalformedURLException;
import java.util.Scanner;

public class client {
    static long bal, deb, crd, ch;
    public static void main(String[] args) {
	
	try {
	    Calc c = (Calc)
		Naming.lookup("rmi://localhost/CalcServer");
	    System.out.println("Helo");
	    Scanner scan = new Scanner(new File("rec.txt"));
	    bal = scan.nextLong();
	    System.out.println("Balance:" + bal);
	    scan.close();
	    System.out.println("Enter amount to debit:");
	    Scanner scan1 = new Scanner(System.in);
	    deb = scan1.nextLong();
	    scan1.close();
	    bal = c.sub(bal, deb);
	    if(bal < 0) System.out.println("Balance < 0..Sorry");
	    else {
		System.out.println("Balance:" + bal);
		PrintWriter pwip = new PrintWriter(new File("rec.txt"));
		pwip.println(bal);
		pwip.close();
	    }
	}  
	catch (RemoteException re){
	    System.out.println("Remote exception" + re);
	}
	catch(NotBoundException ne) {
	    System.out.println("NotBound exception" + ne);
	}
	catch(MalformedURLException me) {
	}
	catch(Exception e) {
	    e.printStackTrace();
	}
	
    }
}