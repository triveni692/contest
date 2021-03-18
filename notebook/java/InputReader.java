package modules;

import java.io.*;
import java.util.StringTokenizer;

/**
 * Created by triveni on 6/7/17.
 */
public class InputReader
{
	public BufferedReader reader;
	public StringTokenizer tokenizer;

	public InputReader(InputStream inputStream)
	{
		reader = new BufferedReader(new InputStreamReader(inputStream));
		tokenizer = null;
	}

	public InputReader(String inputFile) throws FileNotFoundException
	{
		reader = new BufferedReader(new FileReader(inputFile));
		tokenizer = null;
	}

	public String nextLine()
	{
		String curr = "";
		try {
			curr = reader.readLine();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		return curr;
	}

	public String next() {
		return nextString();
	}

	public String nextString()
	{
		while(tokenizer == null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(nextLine());
			} catch (Exception e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}

	public int nextInt()
	{
		return Integer.parseInt(nextString());
	}

	public long nextLong()
	{
		return Long.parseLong(nextString());
	}

	public double nextDouble(){
		return Double.parseDouble(nextString());
	}
}
