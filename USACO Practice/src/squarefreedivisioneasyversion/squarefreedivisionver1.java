//package squarefreedivisioneasyversion;

import java.util.*;
import java.io.*;

public class squarefreedivisionver1 {
	
	public static boolean isSquare(long val) {
		long temp = (long) Math.sqrt(val);
		if(temp * temp == val && val != 1 && val != 0) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			ArrayList<ArrayList<Integer>> segments = new ArrayList<ArrayList<Integer>>();
			segments.add(new ArrayList<Integer>());
			segments.get(0).add(nums[0]);
			for(int i = 1; i < n; i++) {
				int next = nums[i];
				boolean isValid = true;
				for(int j = 0; j < segments.get(segments.size() - 1).size(); j++) {
					if(isSquare(next * segments.get(segments.size() - 1).get(j))) {
						isValid = false;
						break;
					}
				}
				if(isValid) {
					segments.get(segments.size() - 1).add(next);
				}
				else {
					segments.add(new ArrayList<Integer>());
					segments.get(segments.size() - 1).add(next);
				}
			}
			fout.append(segments.size()).append("\n");
		}
		System.out.println(fout);
	}
}
