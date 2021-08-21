//package monotonicrenumeration;

import java.util.*;
import java.io.*;

public class monotonicrenumeration {
	public static void main(String[] args) throws IOException {
		
		//1102E
		
		//define a segment as the space between when you first see a number, x and the last time you see x. If there are two overlapping segments, then all the numbers within the segment in the b
		//array must be equal. To get the answer, you must find the number of non-overlapping segments in the a array, and raise 2 to the power of that number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		HashMap<Integer, Integer> starts = new HashMap<Integer, Integer>();
		HashMap<Integer, Integer> ends = new HashMap<Integer, Integer>();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			if(!starts.containsKey(next)) {
				starts.put(next, i);
				ends.put(next, i);
			}
			else {
				ends.put(next, i);
			}
		}
		int numSegments = -1;
		HashSet<Integer> active = new HashSet<Integer>();
		ArrayList<int[]> segments = new ArrayList<int[]>();
		for(int i : starts.keySet()) {
			segments.add(new int[] {i, starts.get(i)});
		}
		for(int i : ends.keySet()) {
			segments.add(new int[] {i, ends.get(i)});
		}
		segments.sort((a, b) -> a[1] - b[1]);
		for(int i = 0; i < segments.size(); i++) {
			if(active.size() == 0) {
				numSegments ++;
			}
			int next = segments.get(i)[0];
			if(active.contains(next)) {
				active.remove(next);
			}
			else {
				active.add(next);
			}
			//System.out.println(active);
		}
		long mod = 998244353;
		long ans = 1;
		for(int i = 0; i < numSegments; i++) {
			ans *= 2;
			ans %= mod;
		}
		System.out.println(ans);
	}
}
