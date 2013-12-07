import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.net.MalformedURLException;
import java.io.*;
import java.util.Scanner;

public class atm_client{
       static  long bal,deb,ch;
  public static void main(String args[])           
   {
   try{
      atmInt a= (atmInt) Naming.lookup("rmi://localhost/CalcServe");
      bal=500;
      Scanner scan1=new Scanner(new File("customer.txt"));
      bal = scan1.nextLong();  
      scan1.close();       
      System.out.println("\nbalance:"+ bal);
      System.out.println("Enter your choice\n1.Debit\n2.Credit\n3.Display\n4.Exit");
      Scanner scan = new Scanner(System.in);
      ch =scan.nextLong();
      if(ch==1)
      {
      System.out.println("\nenter amt to debit");   
      
      deb=scan.nextLong();
      bal = a.debit(deb,bal);
      System.out.println("\nbalance after debit:"+bal);
      PrintWriter pwInput = new PrintWriter(new File("customer.txt"));
      pwInput.println(bal);
      pwInput.close();
     }
     else if(ch==2)
     {
     System.out.println("in credit");
      }
  } catch(RemoteException e)
   {
     System.out.println("remote exception::"+e);

  }
    catch(NotBoundException n){
     System.out.println("not bound exception::"+n);

  }
   catch(MalformedURLException m){
   System.out.println("malformed exception::"+m);
  }
    catch(FileNotFoundException f)
   {
    System.out.println("file not found: "+ f);
   }
 }


}


 
