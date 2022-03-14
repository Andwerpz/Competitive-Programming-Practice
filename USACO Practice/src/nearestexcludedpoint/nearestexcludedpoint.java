//package nearestexcludedpoint;

import java.util.*;
import java.io.*;

public class nearestexcludedpoint {
	public static void main(String[] args) throws IOException {
		
		//1651D
		
		//first, you can get the solutions to any point with an adjacent point not in the set.
		//these points obviously have a solution with distance = 1. 
		
		//from those points, you can infer that any point that is adjacent to it, that doesn't have any 
		//solutions, has at minimum a solution of distance 2. you can just use the same solution
		//for the first point to the next point.
		
		//do bfs for all the points.
		
		//implementation doesn't work in java, at least mine doesn't
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		HashMap<Pair, Integer> map = new HashMap<>();
		int[][] ans = new int[n][2];
		for (int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			map.put(new Pair(x, y), i);
		}
		boolean[] v = new boolean[n];
		Queue<Pair> q = new ArrayDeque<>();
		int[] dx = new int[] { 1, -1, 0, 0 };
		int[] dy = new int[] { 0, 0, 1, -1 };
		for (Pair cur : map.keySet()) {
			for (int i = 0; i < 4; i++) {
				Pair next = new Pair(cur.first + dx[i], cur.second + dy[i]);
				if (!map.keySet().contains(next)) {
					int id = map.get(cur);
					ans[id][0] = next.first;
					ans[id][1] = next.second;
					q.add(cur);
					v[id] = true;
				}
			}
		}
		while (q.size() != 0) {
			Pair cur = q.poll();
			int curId = map.get(cur);
			for (int i = 0; i < 4; i++) {
				Pair next = new Pair(cur.first + dx[i], cur.second + dy[i]);
				if (!map.containsKey(next)) {
					continue;
				}
				int id = map.get(next);
				if (!v[id]) {
					v[id] = true;
					ans[id][0] = ans[curId][0];
					ans[id][1] = ans[curId][1];
					q.add(next);
				}
			}
		}
		StringBuilder fout = new StringBuilder();
		for (int[] i : ans) {
			fout.append(i[0]).append(" ").append(i[1]).append("\n");
		}
		System.out.print(fout);
	}

}

class Pair {
	public final int first; 
	public final int second; 


	Pair(int first, int second) {
		this.first = first;
		this.second = second;
	}

	@Override
    // Computes hash code for an object to support hash tables
    public int hashCode()
    {
        // use hash codes of the underlying objects
        return 31 * Integer.hashCode(first) + Integer.hashCode(second);
    }
	
	@Override
	// Checks specified object is "equal to" the current object or not
	public boolean equals(Object o) {
		if (this == o) {
			return true;
		}

		if (o == null || getClass() != o.getClass()) {
			return false;
		}

		Pair pair = (Pair) o;

		// call `equals()` method of the underlying objects
		if (first != pair.first) {
			return false;
		}
		return second == pair.second;
	}
}