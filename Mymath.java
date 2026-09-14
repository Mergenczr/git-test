import java.util.Scanner;
public class MyMath {
    public int sum(int a, int b) {
        return a + b;
    }

    public int subtract(int a, int b) {
        return a - b;
    }

    public int multiply(int a, int b) {
        return a * b;
    }

    public double divide(int a, int b) {
        if (b == 0) {
            System.out.println("Error: Division by zero is not allowed.");
            return Double.NaN;
        }
        return (double) a / b;
    }
    public int power(int a, int b) {
        int result = 1;

        for (int i = 0; i < b; i++) {
            result *= a;
        }

        return result;
    }
}

class Calculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        MyMath math = new MyMath();

        System.out.print("enter number");
        String input = scanner.nextLine();

        char operator = ' ';
        int operatorIndex = -1;

        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == '+' || input.charAt(i) == '-' || input.charAt(i) == '*' || input.charAt(i) == '/' || input.charAt(i)=='^') {
                operator = input.charAt(i);
                operatorIndex = i;
                break;
            }
        }

        if (operatorIndex == -1) {
            System.out.println("Invalid input! No valid operator found.");
            return;
        }

        try {
            String firstPart = input.substring(0, operatorIndex).trim();
            int a = Integer.parseInt(firstPart);


            String secondPart = input.substring(operatorIndex + 1).trim();
            int b = Integer.parseInt(secondPart);

            double result = 0;
            switch (operator) {
                case '+':
                    result = math.sum(a, b);
                    break;
                case '-':
                    result = math.subtract(a, b);
                    break;
                case '*':
                    result = math.multiply(a, b);
                    break;
                case '/':
                    result = math.divide(a, b);
                    break;
                case '^':
                    result = math.power(a,b);
                    break;
            }
            System.out.println("Result: " + result);
        } catch (Exception e) {
            System.out.print("Error :" +e.getClass().getSimpleName());
        }


        scanner.close();
    }
}
