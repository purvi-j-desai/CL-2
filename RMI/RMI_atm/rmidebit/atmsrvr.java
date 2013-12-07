import java.rmi.Naming;

public class atmsrvr{
   
    public atmsrvr()
    {
       try{
           atmInt a=new atmImpl();
           Naming.rebind("rmi://localhost:1099/CalcServe",a);
   }catch(Exception e)
    {
        System.out.println("error:::"+e);
    }
  }
 
   public static void main(String args[])
  {
     new atmsrvr(); 
     

 }



}
