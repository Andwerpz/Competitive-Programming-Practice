package catpartyhardedition;

import java.util.*;
import java.io.*;

public class catpartyhardedition {
	
	static TreeMap<Integer, Integer> tree;
	
	public static void main(String[] args) throws IOException {
		
		//1163B2
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		tree = new TreeMap<Integer, Integer>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int max = 0;
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			tree.put(next, tree.getOrDefault(next, 0) + 1);
		}
	}
}	
