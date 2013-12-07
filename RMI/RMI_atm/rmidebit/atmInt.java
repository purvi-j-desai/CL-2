public interface atmInt extends java.rmi.Remote{
   public long debit(long deb,long bal) throws  java.rmi.RemoteException;
   public long credit(long cred,long bal) throws java.rmi.RemoteException;
   public long display(long bal) throws java.rmi.RemoteException;

}
