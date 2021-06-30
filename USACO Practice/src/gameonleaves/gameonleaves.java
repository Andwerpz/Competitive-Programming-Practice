//package gameonleaves;

import java.util.*;
import java.io.*;

public class gameonleaves {
	public static void main(String[] args) throws IOException {
		
		//1363C
		
		//was thinking that if you can't get it on the first turn, then if (n - 2) % 2 == 0, ayush wins, and if (n - 2) % 2 == 1 then ashish wins.
		
		//my thinking is correct.
		
		//imagine a situation where x = 1, and 1 is connected to two other nodes, 2 and 3. Neither person wants to take either 2 or 3, since this means that the other person wins. 
		//generalize this, and we have a situation where if there is a node that once removed, reduces the degree of node x to 1, then neither player can take it since
		//this means that the other person wins. This means that that node will be the last node that is removed. So the game is simplified into: if x can be taken immediately, then 
		//the person who goes first wins, if it can't, then take a look at the number of nodes. If the number of nodes is even, then the player who goes first can force the other person to 
		//take the third to last node, if it's odd, then the person who goes second can force the first person to take the third to last node.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));	//ayush and ashish, ayush moves first always
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
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
			if(c.get(x - 1).size() <= 1) {
				fout.append("Ayush\n");
			}
			else {
				if(n % 2 == 0) {
					fout.append("Ayush\n");
				}
				else {
					fout.append("Ashish\n");
				}
			}
		}
		System.out.print(fout);
	}
}
