//package connectthree;

import java.util.*;
import java.io.*;

public class connectthree {
	
	public static ArrayList<ArrayList<Integer>> getMin(ArrayList<Integer> a, ArrayList<Integer> b, ArrayList<Integer> c) {	//starting from a, getting the min
		ArrayList<ArrayList<Integer>> ans = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> ans2 = new ArrayList<ArrayList<Integer>>();
		int minX = Math.min(Math.min(a.get(0), b.get(0)), c.get(0));
		int maxX = Math.max(Math.max(a.get(0), b.get(0)), c.get(0));
		int minY = Math.min(Math.min(a.get(1), b.get(1)), c.get(1));
		int maxY = Math.max(Math.max(a.get(1), b.get(1)), c.get(1));
		//check starting in the x direction
		for(int i = minX; i <= maxX; i++) {
			ans.add(new ArrayList<Integer>(Arrays.asList(i, a.get(1))));
		}
		for(int i = Math.min(a.get(1), b.get(1)); i <= Math.max(a.get(1), b.get(1)); i++) {
			ans.add(new ArrayList<Integer>(Arrays.asList(b.get(0), i)));
		}
		for(int i = Math.min(a.get(1), c.get(1)); i <= Math.max(a.get(1), c.get(1)); i++) {
			ans.add(new ArrayList<Integer>(Arrays.asList(c.get(0), i)));
		}
		//check starting in the y direction
		for(int i = minY; i <= maxY; i++) {
			ans2.add(new ArrayList<Integer>(Arrays.asList(a.get(0), i)));
		}
		for(int i = Math.min(a.get(0), b.get(0)); i <= Math.max(a.get(0), b.get(0)); i++) {
			ans2.add(new ArrayList<Integer>(Arrays.asList(i, b.get(1))));
		}
		for(int i = Math.min(a.get(0), c.get(0)); i <= Math.max(a.get(0), c.get(0)); i++) {
			ans2.add(new ArrayList<Integer>(Arrays.asList(i, c.get(1))));
		}
		//now remove duplicates
		HashSet<ArrayList<Integer>> set = new HashSet<ArrayList<Integer>>();
		for(ArrayList<Integer> i : ans) {
			set.add(i);
		}
		ans = new ArrayList<ArrayList<Integer>>();
		for(ArrayList<Integer> i : set) {
			ans.add(i);
		}
		set = new HashSet<ArrayList<Integer>>();
		for(ArrayList<Integer> i : ans2) {
			set.add(i);
		}
		ans2 = new ArrayList<ArrayList<Integer>>();
		for(ArrayList<Integer> i : set) {
			ans2.add(i);
		}
//		System.out.println(ans);
//		System.out.println(ans2);
		if(ans.size() < ans2.size()) {
			return ans;
		}
		else {
			return ans2;
		}
	}
	
	public static boolean isEqual(int[] a, int[] b) {
		return a[0] == b[0] && a[1] == b[1];
	}
	
	public static void main(String[] args) throws IOException {
		
		//1085C
		
		//my implementation is so bad lol. Idk how to make it better tho.
		
		//the optimal strategy is to try to make one tile connect to the other two tiles. 
		//consider one selected tile at a time. You can consider x first, or y first. Extend one coordinate out so that it covers all three tiles, then draw the other coordinate out
		//so that it connects with the other tiles. Repeat for each coordinate, and each starting tile. The minimum is the answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<ArrayList<Integer>> points = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < 3; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			points.add(new ArrayList<Integer>());
			points.get(i).add(Integer.parseInt(st.nextToken()));
			points.get(i).add(Integer.parseInt(st.nextToken()));
		}
		ArrayList<ArrayList<Integer>> ans = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < 3; i++) {
			ArrayList<ArrayList<Integer>> next = getMin(points.get(i), points.get((i + 1) % 3), points.get((i + 2) % 3));
			if(i == 0 || ans.size() > next.size()) {
				ans = next;
			}
		}
		StringBuilder fout = new StringBuilder();
		fout.append(ans.size()).append("\n");
		for(int i = 0; i < ans.size(); i++) {
			fout.append(ans.get(i).get(0)).append(" ").append(ans.get(i).get(1)).append("\n");
		}
		System.out.print(fout);
	}
}
