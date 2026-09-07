import java.util.ArrayDeque;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class ComparacionEstructuras {

    static final int N = 200_000;

    public static void main(String[] args) {
        System.out.printf("%-12s %-10s %-10s %-12s%n", "Estructura", "Operacion", "N", "Tiempo(ms)");
        medirPila();
        medirCola();
    }

    private static void medirPila() {
        Stack<Integer> stack = new Stack<>();
        long inicio = System.nanoTime();
        for (int i = 0; i < N; i++) stack.push(i);
        for (int i = 0; i < N; i++) stack.pop();
        long finStack = (System.nanoTime() - inicio) / 1_000_000;

        Deque<Integer> arrayDeque = new ArrayDeque<>();
        inicio = System.nanoTime();
        for (int i = 0; i < N; i++) arrayDeque.push(i);
        for (int i = 0; i < N; i++) arrayDeque.pop();
        long finArrayDeque = (System.nanoTime() - inicio) / 1_000_000;

        System.out.printf("%-12s %-10s %-10d %-12d%n", "Stack", "push/pop", N, finStack);
        System.out.printf("%-12s %-10s %-10d %-12d%n", "ArrayDeque", "push/pop", N, finArrayDeque);
    }

    private static void medirCola() {
        Queue<Integer> linkedList = new LinkedList<>();
        long inicio = System.nanoTime();
        for (int i = 0; i < N; i++) linkedList.offer(i);
        for (int i = 0; i < N; i++) linkedList.poll();
        long finLinkedList = (System.nanoTime() - inicio) / 1_000_000;

        Queue<Integer> arrayDeque = new ArrayDeque<>();
        inicio = System.nanoTime();
        for (int i = 0; i < N; i++) arrayDeque.offer(i);
        for (int i = 0; i < N; i++) arrayDeque.poll();
        long finArrayDeque = (System.nanoTime() - inicio) / 1_000_000;

        System.out.printf("%-12s %-10s %-10d %-12d%n", "LinkedList", "offer/poll", N, finLinkedList);
        System.out.printf("%-12s %-10s %-10d %-12d%n", "ArrayDeque", "offer/poll", N, finArrayDeque);
    }
}