package Mainn;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {

    private static List<Produs> produse = new ArrayList<>();
    private static JTextField textField_1;
    private static JTextField textField;
    private static JTextField textField_2;
    private static JTable table;

    private static final String FILENAME = "C:\\Users\\ффф\\eclipse-workspace\\Proiect_P3\\Produs";

    public static void serializeProduse(List<Produs> produse) {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILENAME))) {
            oos.writeObject(produse);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static List<Produs> deserializeProduse() {
        List<Produs> produse = new ArrayList<>();
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILENAME))) {
            produse = (List<Produs>) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return produse;
    }

    public static void adaugaProdus(Produs produs, List<Produs> produse) {
        produse.add(produs);
        serializeProduse(produse);
    }

    public static Produs cautaProdus(String nume, List<Produs> produse) {
        for (Produs produs : produse) {
            if (produs.getNume().equals(nume)) {
                return produs;
            }
        }
        return null;
    }

    public static void stergeProdus(String nume, List<Produs> produse) {
        Produs produs = cautaProdus(nume, produse);
        if (produs != null) {
            produse.remove(produs);
            serializeProduse(produse);
            System.out.println("Produs șters cu succes.");
        } else {
            System.out.println("Produsul nu a fost găsit.");
        }
    }
    
    public static void modificaProdus(String nume,int cantitate, List<Produs> produse) {
        Produs produs = cautaProdus(nume, produse);
        if (produs != null) {
            produs.setCantitate(cantitate);
            serializeProduse(produse);
            System.out.println("Produs modificat cu succes.");
        } else {
            System.out.println("Produsul nu a fost găsit.");
        }
    }

    public static void main(String[] args) {
        produse = deserializeProduse();

        JFrame frame = new JFrame("Electronics Shop");

        frame.setSize(850, 450);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel inputPanel = createInputPanel();
        table = createProductTable();

        frame.add(inputPanel, BorderLayout.NORTH);
        frame.add(new JScrollPane(table), BorderLayout.CENTER);

        frame.setVisible(true);
        

    }

    private static JPanel createInputPanel() {
        JPanel mainInputPanel = new JPanel(new BorderLayout());

        JPanel actionPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 5, 5));

        textField_1 = new JTextField();
        textField_1.setColumns(10);

        textField = new JTextField();
        textField.setColumns(10);

        textField_2 = new JTextField();
        textField_2.setColumns(10);

        JButton btnNewButton = new JButton("Adaugare");
        btnNewButton.setFont(new Font("Stencil", Font.PLAIN, 12));
        btnNewButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addProduct();
            }
        });

        JButton btnStergere = new JButton("Stergere");
        btnStergere.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                removeProduct();
            }
        });
        btnStergere.setFont(new Font("Stencil", Font.PLAIN, 12));

        JButton btnModifica = new JButton("Modifica");
        btnModifica.setFont(new Font("Stencil", Font.PLAIN, 12));
        btnModifica.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                modifyProduct();
            }
        });

        actionPanel.add(new JLabel("Nume produs:"));
        actionPanel.add(textField);
        actionPanel.add(new JLabel("Categoria:"));
        actionPanel.add(textField_1);
        actionPanel.add(new JLabel("Cantitate:"));
        actionPanel.add(textField_2);
        actionPanel.add(btnNewButton);
        actionPanel.add(btnStergere);
        actionPanel.add(btnModifica);

        JPanel searchFilterPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 7, 7));

        JTextField searchTextField = new JTextField();
        searchTextField.setColumns(10);

        JButton searchButton = new JButton("Cauta dupa Nume");
        searchButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                searchByName(searchTextField.getText());
            }
        });

        searchFilterPanel.add(new JLabel("Cauta dupa Nume:"));
        searchFilterPanel.add(searchTextField);
        searchFilterPanel.add(searchButton);

        JButton filterButton = new JButton("Cantitate redusă");
        filterButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                filterByQuantity();
            }
        });

        searchFilterPanel.add(filterButton);

        mainInputPanel.add(actionPanel, BorderLayout.NORTH);
        mainInputPanel.add(searchFilterPanel, BorderLayout.SOUTH);

        return mainInputPanel;
    }

    

    private static JTable createProductTable() {
        String[] columnNames = {"Denumire produs", "Cantitate"};

        DefaultTableModel tableModel = new DefaultTableModel(columnNames, 0);

        JTable productTable = new JTable(tableModel);

        for (Produs produs : produse) {
            tableModel.addRow(new Object[]{produs.getNume(), produs.getCantitate()});
        }

        return productTable;
    }


    
    private static void addProduct() {
        String numeProdus = textField.getText();
        String categoria = textField_1.getText();
        String cantitateText = textField_2.getText();

        try {
            int cantitate = Integer.parseInt(cantitateText);

            Produs produs = new Produs(categoria, numeProdus, cantitate);
            adaugaProdus(produs, produse);

            DefaultTableModel model = (DefaultTableModel) table.getModel();
            model.addRow(new Object[]{produs.getNume(), produs.getCantitate()});
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Introduceți o cantitate validă (număr întreg).", "Eroare", JOptionPane.ERROR_MESSAGE);
        }
    }


    
    private static void removeProduct() {
        int selectedRow = table.getSelectedRow();

        if (selectedRow != -1) {
            String numeProdus = (String) table.getValueAt(selectedRow, 0);
            stergeProdus(numeProdus, produse);
           
            DefaultTableModel model = (DefaultTableModel) table.getModel();
            model.removeRow(selectedRow);
        } else {
            JOptionPane.showMessageDialog(null, "Selectați un produs pentru a-l șterge.", "Eroare", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    
    
    private static void modifyProduct() {
        int selectedRow = table.getSelectedRow();

        if (selectedRow != -1) {
            String numeProdus = textField.getText();
            String categoria = textField_1.getText();
            String cantitateText = textField_2.getText();

            try {
                int cantitate = Integer.parseInt(cantitateText);

                if(cantitate == 0) {
                	stergeProdus(numeProdus, produse);
                	DefaultTableModel model = (DefaultTableModel) table.getModel();
                    model.removeRow(selectedRow);
                }
                else {
                modificaProdus(numeProdus,cantitate,produse);
                
                Produs produs = produse.get(selectedRow);
                produs.setNume(numeProdus);
                produs.setCantitate(cantitate);

                DefaultTableModel model = (DefaultTableModel) table.getModel();
                model.setValueAt(produs.getNume(), selectedRow, 0);
                model.setValueAt(produs.getCantitate(), selectedRow, 1);
               
            }} catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(null, "Introduceți o cantitate validă (număr întreg).", "Eroare", JOptionPane.ERROR_MESSAGE);
            }
            
        } else {
            JOptionPane.showMessageDialog(null, "Selectați un produs pentru a-l modifica.", "Eroare", JOptionPane.ERROR_MESSAGE);
        }
    }
    
    
    
    private static void searchByName(String numeCautat) {
        DefaultTableModel model = (DefaultTableModel) table.getModel();
        model.setRowCount(0);

        for (Produs produs : produse) {
            if (produs.getNume().equalsIgnoreCase(numeCautat)) {
                model.addRow(new Object[]{produs.getNume(), produs.getCantitate()});
            }
        }
    }
    
    
    
    private static void filterByQuantity() {
        DefaultTableModel model = (DefaultTableModel) table.getModel();
        model.setRowCount(0);

        for (Produs produs : produse) {
            if (produs.getCantitate() < 3) {
                model.addRow(new Object[]{produs.getNume(), produs.getCantitate()});
            }
        }
    }

    
    
}
