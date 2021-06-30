//package phoenixandtowers;

import java.util.*;
import java.io.*;

public class phoenixandtowersver1 {
	public static void main(String[] args) throws IOException {
		
		//solution gets correct answer, just the implementation is bad. We need a way to get the tower with the least height in at least O(log(n)) time.
		
		//too many sets lol
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			TreeMap<Integer, HashSet<Integer>> towerSize = new TreeMap<Integer, HashSet<Integer>>();	//save the size of the tower as the key, and the list of towers that size as the value
			int[] nums = new int[n];	//for each segment, stores which tower it belongs to.
			int[] segments = new int[n];	//stores the size of each segment
			HashSet<Integer> initial = new HashSet<Integer>();
			for(int i = 0; i < m; i++) {
				initial.add(i);
			}
			towerSize.put(0, initial);
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				segments[i] = Integer.parseInt(st.nextToken());
			}
			fout.append("YES\n");
			for(int i = 0; i < n; i++) {
				int key = towerSize.firstKey();
				int nextId = towerSize.get(key).iterator().next();
				towerSize.get(key).remove(nextId);
				if(towerSize.get(key).size() == 0) {
					towerSize.remove(key);
				}
				int size = segments[i] + key;
				fout.append(nextId + 1).append(" ");
				if(towerSize.containsKey(size)) {
					towerSize.get(size).add(nextId);
				}
				else {
					HashSet<Integer> newSet = new HashSet<Integer>();
					newSet.add(nextId);
					towerSize.put(size, newSet);
				}
				//System.out.println(towerSize);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
