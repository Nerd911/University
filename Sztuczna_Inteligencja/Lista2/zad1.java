import java.io.*;
import java.util.*;

public class zad1 {

	static int nr_of_rows, nr_of_columns;
	static int[][]rows, cols;
	static long[]board;
	static long[][]rowPermutations;
	public static void main(String[] args) throws Exception {
		final InputReader in = new InputReader(new FileInputStream("zad_input.txt"));
		final OutputWriter out = new OutputWriter(new FileOutputStream("zad_output.txt"));
		nr_of_rows = in.readInt();
		nr_of_columns = in.readInt();
		{
			rows = new int[nr_of_rows][];
			for(int r=0;r<nr_of_rows;r++){
				String[] line = in.readLine().split(" ");
				rows[r] = new int[line.length];
				for(int i=0;i<line.length;i++){
					rows[r][i] = Integer.parseInt(line[i]);
				}
			}
			cols = new int[nr_of_columns][];
			for(int c=0;c<nr_of_columns;c++){
				String[] line = in.readLine().split(" ");
				cols[c] = new int[line.length];
				for(int i=0;i<line.length;i++){
					cols[c][i] = Integer.parseInt(line[i]);
				}
			}
			board = new long[nr_of_rows];
		}
		// permutacje
		rowPermutations = new long[nr_of_rows][];
		for(int r=0;r<nr_of_rows;r++){
			LinkedList<Long> res = new LinkedList<Long>();
			int spaces = nr_of_columns - (rows[r].length-1);
			for(int i=0;i<rows[r].length;i++){
				spaces -= rows[r][i];
			}
			calcPermutations(r, 0, spaces, 0, 0,res);
			rowPermutations[r] = new long[res.size()];
			while(!res.isEmpty()){
				rowPermutations[r][res.size()-1]=res.pollLast();
			}
		}
		columnValues = new int[nr_of_rows][nr_of_columns];
		columnIndices = new int[nr_of_rows][nr_of_columns];
		if(dfs(0)){
			for(int r=0;r<nr_of_rows;r++){
				for(int c=0;c<nr_of_columns;c++){
					out.print((board[r]&(1L<<c))==0 ? '.' : '#');
				}
				out.printLine();
			}
		}
		out.close();
	}

	static int[][]columnValues, columnIndices;
	static boolean dfs(int row){
		if(row==nr_of_rows){
			for(int c=0;c<nr_of_columns;c++){
				if(columnIndices[nr_of_rows-1][c]==cols[c].length
					|| (columnIndices[nr_of_rows-1][c] == cols[c].length-1
						&& columnValues[nr_of_rows-1][c] == cols[c][columnIndices[nr_of_rows-1][c]])){
					continue;
				}
				return false;
			}
			return true;
		}
		for(int i=0;i<rowPermutations[row].length;i++){
			board[row] = rowPermutations[row][i];
			if(updateColumns(row)){
				if(dfs(row+1)){
					return true;
				}
			}
		}
		return false;
	}

	static void calcPermutations(int r, int cur, int spaces, long perm, int shift, LinkedList<Long> res){
		if(cur == rows[r].length){
			if((board[r]&perm)==board[r]){
				res.add(perm);
			}
			return;
		}
		while(spaces>=0){
			calcPermutations(r, cur+1, spaces, perm|(bits(rows[r][cur])<<shift), shift+rows[r][cur]+1,res);
			shift++;
			spaces--;
		}
	}

	static boolean updateColumns(int row){
		if(row==0){
			for(int c=0,ixc=1;c<nr_of_columns;c++,ixc<<=1){
				if((board[0]&ixc)!=0){
					columnValues[0][c]=1;
				}else{
					columnValues[0][c]=0;
				}
			}
			return true;
		}
		for(int c=0,ixc=1;c<nr_of_columns;c++,ixc<<=1){
			columnValues[row][c]=columnValues[row-1][c];
			columnIndices[row][c]=columnIndices[row-1][c];
			if((board[row]&ixc)!=0){
				if(columnValues[row-1][c] == 0 && columnIndices[row-1][c]==cols[c].length){
					return false;
				}
				if(cols[c][columnIndices[row-1][c]]==columnValues[row-1][c]){
					return false;
				}
				columnValues[row][c]++;
			}else{
				if(columnValues[row-1][c] > 0){
					if(cols[c][columnIndices[row-1][c]]!=columnValues[row-1][c]){
						return false;
					}
					columnValues[row][c]=0;
					columnIndices[row][c]++;
				}
			}
		}
		return true;
	}

	static long bits(int b){
		return (1L<<b)-1;
	}

	static class InputReader {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;

		public InputReader(InputStream stream) {
			this.stream = stream;
		}

		public int read() {
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		public String readString() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		public String readLine() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isEndOfLine(c));
			return res.toString();
		}

		public int readInt() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			int res = 0;
			do {
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public long readLong() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = read();
			}
			long res = 0;
			do {
				res *= 10;
				res += c - '0';
				c = read();
			} while (!isSpaceChar(c));
			return res * sgn;
		}

		public boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		public boolean isEndOfLine(int c) {
			return c == '\n' || c == -1;
		}
	}

	static class OutputWriter {
		private final PrintWriter writer;

		public OutputWriter(OutputStream outputStream) {
			writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(
					outputStream)));
		}

		public OutputWriter(Writer writer) {
			this.writer = new PrintWriter(writer);
		}

		public void close() {
			writer.close();
		}
		public void print(Object... objects) {
			for (int i = 0; i < objects.length; i++) {
				if (i != 0)
					writer.print(' ');
				writer.print(objects[i]);
			}
		}

		public void printLine(Object... objects) {
			print(objects);
			writer.println();
		}
	}
}
