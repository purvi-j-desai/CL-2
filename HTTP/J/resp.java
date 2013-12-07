import java.net.URL;
import java.net.URLConnection;

public class resp {
    public static void main(String[] args) 
	throws Exception {
	try {
	    URL u = new URL("http://localhost/index.html");
	    URLConnection conn = u.openConnection(); 
	    for(int i = 0; ; i++) {
		String name = conn.getHeaderFieldKey(i);
		String value = conn.getHeaderField(i);
		if(name == null && value == null)
		    break;
		else if(name == null)
		    System.out.println(value);
		else 
		    System.out.println(name+ ": "+ value);
	    }
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
}