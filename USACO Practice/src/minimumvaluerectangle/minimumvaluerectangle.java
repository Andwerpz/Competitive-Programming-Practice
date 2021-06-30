//package minimumvaluerectangle;

import java.util.*;
import java.io.*;

public class minimumvaluerectangle {
	public static void main(String[] args) throws IOException {
		
		//1027C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashSet<Long> seen = new HashSet<Long>();
			ArrayList<Long> sticks = new ArrayList<Long>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				long next = Integer.parseInt(st.nextToken());
				if(!seen.contains(next)) {
					seen.add(next);
				}
				else {
					seen.remove(next);
					sticks.add(next);
				}
			}
			sticks.sort((a, b) -> Long.compare(a, b));
			int index = 0;
			double min = Double.MAX_VALUE;
			for(int i = 0; i < sticks.size() - 1; i++) {
				long perimeter = sticks.get(i) * 2 + sticks.get(i + 1) * 2;
				long area = sticks.get(i) * sticks.get(i + 1);
				double cur = (double) perimeter / (double) area * perimeter;
				//System.out.println("RATIO: " + cur + " " + sticks.get(i) + " " + sticks.get(i + 1));
				if(cur < min) {
					min = cur;
					index = i;
				}
			}
			fout.append(sticks.get(index)).append(" ").append(sticks.get(index)).append(" ").append(sticks.get(index + 1)).append(" ").append(sticks.get(index + 1)).append("\n");
		}
		System.out.print(fout);
	}
}
