//package unclebogdanandcountryhappiness;

import java.util.*;
import java.io.*;

public class unclebogdanandcountryhappiness {
	
	static int[] numPeople, happiness, numHere;
	static ArrayList<ArrayList<Integer>> c;
	
	public static void getPeople(int node, int prev) {
		numPeople[node] = numHere[node];
		for(int i = 0; i < c.get(node).size(); i++) {
			int next = c.get(node).get(i);
			if(next != prev) {
				getPeople(next, node);
				numPeople[node] += numPeople[next];
			}
		}
	}
	
	public static boolean isValid(int node, int prev) {
		//System.out.println(node);
		long totalPeople = numPeople[node];
		long happy = (totalPeople + happiness[node]) / 2;
		long unhappy = totalPeople - happy;
		if(happy < 0 || unhappy < 0 || (totalPeople + happiness[node]) % 2 != 0) {
			return false;
		}
		unhappy -= numHere[node];
		if(unhappy < 0) {
			happy += unhappy;
			unhappy = 0;
		}
		//System.out.println("HAPPY: " + happy + " UNHAPPY: " + unhappy);
		for(int i = 0; i < c.get(node).size(); i++) {
			int next = c.get(node).get(i);
			if(next != prev) {
				long nextHappy = (numPeople[next] + happiness[next]) / 2;
				long nextUnhappy = numPeople[next] - nextHappy;
				unhappy -= nextUnhappy;
				if(unhappy < 0) {
					happy += unhappy;
					unhappy = 0;
				}
				happy -= nextHappy;
				if(happy < 0) {
					return false;
				}
				if(!isValid(next, node)) {
					return false;
				}
			}
			
		}
		if(happy != 0 || unhappy != 0) {
			return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1388C
		
		//make sure to completely read the problem statement, the trouble was that edges were not presented in any order, either node of the edge could be placed first.
		
		//simple recursive problem. Look at the root node, and calculate how many people are happy and unhappy based on the happiness index of the city. If there are any people living in that 
		//city, first assume that they are unhappy. This is optimal, since you want to conserve the count of happy people for later down the line, since happy people can turn unhappy, 
		//but not the other way around. Then, once you subtracted the people living in the city, look at all the roads leading away from the city. For each city that this one is connected to, 
		//subtract the amount of unhappy people from the next city from this city's count of unhappy people. If there are too much from the next city, then subtract the remaining count from the 
		//happy people. Continue until you have considered all connecting cities. Now, at this point, if the input is valid, then we should have a count of exactly 0 happy and 0 unhappy. If 
		//there are any more or less, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			numHere = new int[n];
			numPeople = new int[n];	//num people in each subtree, with root at node 0
			happiness = new int[n];
			for(int i = 0; i < n; i++) {
				numHere[i] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				happiness[i] = Integer.parseInt(st.nextToken());
			}
			c = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n - 1; i++) {
				st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				c.get(a).add(b);
				c.get(b).add(a);
			}
			getPeople(0, -1);
			fout.append(isValid(0, -1)? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
