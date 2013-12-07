					RMI Client

___________________________________________________________________________________

import java.lang.Integer;
import java.rmi.Naming;
import java.util.HashSet;
import java.util.Set;
import java.io.*;

public class RMIClient {
    public static void main(String[] args) {
        try{
            SetInterface s=(SetInterface) 
			Naming.lookup("rmi://172.16.26.212/SetOperationsService");
            Set<Integer> setA = new HashSet<Integer>();
            Set<Integer> setB = new HashSet<Integer>();

            System.out.println("\n\t Enter the elements of the first set 
									(* to end):- ");

            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String x;
            x = br.readLine();

            while(!x.equals("*"))
            {
                setA.add(Integer.parseInt(x));
                x = br.readLine();
            }

            System.out.println("\n\t Enter the elements of the second set (* to end):- ");
            x = br.readLine();

            while(!x.equals("*"))
            {
                setB.add(Integer.parseInt(x));
                x = br.readLine();
            }
            System.out.println("The set A is :- " + setA);
            System.out.println("The set B is :- " + setB);
            System.out.println("The union of the two sets is :- " + 
						s.union(setA,setB));
            System.out.println("The intersection of the two sets is :- " + 
						s.intersection(setA, setB));
            System.out.println("The difference of the two sets is :- " + 
						s.difference(setA, setB));

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


________________________________________________________________________________________________