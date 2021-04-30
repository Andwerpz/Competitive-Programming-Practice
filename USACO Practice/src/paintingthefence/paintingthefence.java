//package paintingthefence;

import java.util.*;
import java.io.*;

public class paintingthefence {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		int numPainted = 0;
		int[] alone = new int[q];	//for each painter, how many segments they paint alone
		int[][] together = new int[q][q];	//for each painter, how many segments they paint with that other painter
		int[][] times = new int[q * 2][2];	//[0] for the time, [1] for the id
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken()) + 1;	//making the high boundary exclusive
			times[i] = new int[] {a, i};
			times[i + q] = new int[] {b, i};
		}
		Arrays.sort(times, (a, b) -> a[0] - b[0]);
		TreeSet<Integer> active = new TreeSet<Integer>();
		int prev = times[0][0];
		//System.out.println(active + " " + times[i][0]);
		for(int i = 0; i < times.length; i += 0) {
			//System.out.println(prev + " " + times[i][0]);
			int elapsed = times[i][0] - prev;
			prev = times[i][0];
			if(active.size() != 0) {
				numPainted += elapsed;
			}
			if(active.size() == 1) {
				alone[active.first()] += elapsed;
			}
			else if(active.size() == 2) {
				int a = active.first();
				int b = active.last();
				together[a][b] += elapsed;
			}
			while(i != times.length && times[i][0] == prev) {
				int id = times[i][1];
				if(active.contains(id)) {
					active.remove(id);
				}
				else {
					active.add(id);
				}
				i++;
			}//System.out.println(active + " " + times[i][0]);
			//i--;
		}
		//System.out.println(numPainted);
		int min = -1;
		for(int i = 0; i < q; i++) {
			for(int j = i + 1; j < q; j++) {
				int next = alone[i] + alone[j];
				next += together[i][j];
				if(min == -1 || min > next) {
					min = next;
				}
			}
		}
		System.out.println(numPainted - min);
	}
}
