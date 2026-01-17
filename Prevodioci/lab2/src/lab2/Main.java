package lab2;

import java.io.FileInputStream;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java lab2.Main <input_file>");
            return;
        }

        String inputFile = args[0];

        try (FileInputStream fis = new FileInputStream(inputFile)) {

            MPLexer lexer = new MPLexer(fis);


            SintaksniAnalizator parser = new SintaksniAnalizator();


            boolean ok = parser.parse(lexer);

            if (ok) {
                System.out.println("Syntax OK");
            } else {
                System.out.println("Syntax error");
            }

        } catch (IOException e) {
            System.err.println("Error reading file: " + inputFile);
            e.printStackTrace();
        }
    }
}
