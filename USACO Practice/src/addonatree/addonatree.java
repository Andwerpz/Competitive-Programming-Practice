//package addonatree;

import java.util.*;
import java.io.*;

public class addonatree {
	public static void main(String[] args) throws IOException {
		
		//1188A1
		
		//if there is a node of degree two anywhere inside the graph, then the entire thing is invalid. This is because in order to change one edge
		//of that node, you have to change the other edge, thus the two edges have to be the same value.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nodes = new int[n];
		for(int i = 0; i < n - 1; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			nodes[a] ++;
			nodes[b] ++;
		}
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			if(nodes[i] == 2) {
				isValid = false;
				break;
			}
		}
		System.out.println(isValid? "YES" : "NO");
	}
}
