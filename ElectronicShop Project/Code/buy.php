<?php
session_start();
require_once 'connection.php';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $items = json_decode(file_get_contents('php://input'), true);

    foreach ($items as $item) {
        $productId = $item['id'];
        $quantityToBuy = $item['cantitate'];

        $checkAvailabilityQuery = "SELECT cantitate FROM product1 WHERE ID = '$productId'";
        $availabilityResult = $conn->query($checkAvailabilityQuery);

        if ($availabilityResult->num_rows > 0) {
            $row = $availabilityResult->fetch_assoc();
            $currentQuantity = $row['cantitate'];

            if ($currentQuantity >= $quantityToBuy) {
                // Actualizare cantitate în baza de date
                $newQuantity = $currentQuantity - $quantityToBuy;
                $updateQuantityQuery = "UPDATE product1 SET cantitate = '$newQuantity' WHERE ID = '$productId'";
                $conn->query($updateQuantityQuery);
            } else {
                // Nu există suficiente produse disponibile
                echo json_encode(['success' => false, 'message' => "Nu există suficiente produse disponibile pentru ID-ul $productId."]);
                exit();
            }
        }
    }

    // Răspuns de succes către client
    echo json_encode(['success' => true, 'message' => 'Cumpărarea a fost realizată cu succes!']);
} else {
    // Trimitere eroare dacă nu este o cerere POST
    echo json_encode(['success' => false, 'message' => 'Metoda de cerere invalidă.']);
}
?>