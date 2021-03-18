/*
ID: andwerp1
LANG: JAVA
TASK: concerttickets
*/

package concerttickets;

import java.io.*;
import java.util.*;

public class concertticketsver1 {
	
	//use a multiset and use the floor function to find the greatest ticket less than or equal to the buyers max price
	
	public static void main (String [] args) throws IOException {
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    TreeSet<Integer> tickets = new TreeSet<Integer>();
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 0; i < n; i++) {
    	tickets.add(Integer.parseInt(st.nextToken()));
    }
    
    System.out.println(tickets);
    
    
    fin.close();
    
	}
}