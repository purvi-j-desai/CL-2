public class CalcImpl extends java.rmi.server.UnicastRemoteObject
    implements Calc {
    public CalcImpl()
	throws java.rmi.RemoteException {
	super();
    }
    public long add(long a, long b)
	throws java.rmi.RemoteException {
	return a+b;
    }
    public long sub(long a, long b)
	throws java.rmi.RemoteException {
	return a-b;
    }
}