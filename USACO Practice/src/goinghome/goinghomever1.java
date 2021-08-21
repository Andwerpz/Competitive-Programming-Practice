//package goinghome;

import java.util.*;
import java.io.*;

public class goinghomever1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		Integer[] nums = new Integer[n];
		TreeSet<Integer> dict = new TreeSet<Integer>();
		HashMap<Integer, Pair> index = new HashMap<Integer, Pair>();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		boolean isValid = false;
		outer:
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				int diff = Math.abs(nums[i] - nums[j]);
				if(dict.contains(diff) && !index.get(diff).contains(i) && !index.get(diff).contains(j)) {
					isValid = true;
					int[][] ids = new int[4][2];
					ids[0] = new int[] {i + 1, nums[i]};
					ids[1] = new int[] {j + 1, nums[j]};
					int a = index.get(diff).a;
					ids[2] = new int[] {a + 1, nums[a]}; 
					a = index.get(diff).b;
					ids[3] = new int[] {a + 1, nums[a]};
					Arrays.sort(ids, (c, b) -> Integer.compare(c[1], b[1]));
					System.out.print("YES\n");
					System.out.println(ids[0][0] + " " + ids[3][0] + " " + ids[1][0] + " " + ids[2][0]);
					break outer;
				}
				else if(!dict.contains(diff)){
					index.put(diff, new Pair(i, j));
					dict.add(diff);
				}
			}
		}
		if(!isValid) {
			System.out.println("NO\n");
		}
	}
}

class Pair {
	
	public int a, b;
	
	public Pair(int a, int b) {
		this.a = a;
		this.b = b;
	}
	
	public boolean contains(int x) {
		if(x == a || x == b) {
			return true;
		}
		return false;
	}
}
