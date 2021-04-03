package snacktower;

import java.util.*;
import java.io.*;

public class snacktowerver1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int pointer = n;
		StringBuilder fout = new StringBuilder();
		ArrayList<Integer> reserve = new ArrayList<Integer>();
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			reserve.add(next);
			if(next == pointer) {
				reserve.sort((a, b) -> a - b);
				int prev = next + 1;
				while(reserve.size() != 0 && reserve.get(reserve.size() - 1) + 1 == prev) {
					prev = reserve.remove(reserve.size() - 1);
					fout.append(prev).append(" ");
				}
				pointer = prev - 1;
			}
			fout.append("\n");
		}
		System.out.println(fout);
	}
}
