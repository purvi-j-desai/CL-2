public class atmImpl extends java.rmi.server.UnicastRemoteObject implements atmInt{
   
   public atmImpl() throws java.rmi.RemoteException{

  super();
  }
  public long debit(long deb,long bal)throws  java.rmi.RemoteException {
    return(bal-deb);
  
 } 
  public long credit(long cred,long bal)throws  java.rmi.RemoteException {
    return(bal+cred);
  
 } 
public long display(long bal)throws  java.rmi.RemoteException{
    return(bal);
  
 } 


}
