import numpy as np
import cv2
import matplotlib.pyplot as plt


def morphological_reconstruction(marker: np.ndarray, mask: np.ndarray):
    kernel = np.ones(shape=(7, 7), dtype=np.uint8) * 255
    while True:
        expanded = cv2.dilate(src=marker, kernel=kernel)
        expanded = cv2.bitwise_and(src1=expanded, src2=mask)

        if (marker == expanded).all():
            return expanded
        marker = expanded


if __name__ == '__main__':

    img = cv2.imread("coins.png")
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    plt.title('Pocetna slika')
    plt.imshow(img)
    plt.show()

    if True:
        img_median = cv2.medianBlur(img, 11)
        plt.title('Median blur')
        plt.imshow(img_median)
        plt.show()
    else:
        img_median = img


    img_gray = cv2.cvtColor(img_median, cv2.COLOR_RGB2GRAY)
    plt.imshow(img_gray, cmap='gray')
    plt.title('Siva')
    plt.show()

    _, coins_mask = cv2.threshold(img_gray, 220, 255, cv2.THRESH_BINARY_INV)
    plt.title('Threshold maska')
    plt.imshow(coins_mask, cmap='gray')
    plt.show()

    coins_mask = cv2.morphologyEx(coins_mask, cv2.MORPH_CLOSE, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5)))
    plt.title('Zatvaranje maske')
    plt.imshow(coins_mask, cmap='gray')
    plt.show()
    coins_mask = cv2.morphologyEx(coins_mask, cv2.MORPH_OPEN, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5)))
    plt.title('Otvaranje maske')
    plt.imshow(coins_mask, cmap='gray')
    plt.show()

    img_HSV = cv2.cvtColor(img_median, cv2.COLOR_BGR2HSV)
    img_sat = img_HSV[:, :, 1]
    plt.title('Izdvojen Saturation')
    plt.imshow(img_sat)
    plt.show()


    #60
    _, coin_mask = cv2.threshold(img_sat, 60, 255, cv2.THRESH_BINARY)
    plt.title('Bakarni novcic')
    plt.imshow(coin_mask, cmap='gray')
    plt.show()

    coin_mask = cv2.morphologyEx(coin_mask, cv2.MORPH_CLOSE, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5)))
    coin_mask = cv2.morphologyEx(coin_mask, cv2.MORPH_OPEN, cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5)))
    plt.title('Primenjeno otvaranje na bakarni novcic')
    plt.imshow(coin_mask, cmap='gray')
    plt.show()

    coin_mask = morphological_reconstruction(coin_mask, coins_mask)
    coin = cv2.bitwise_and(img, img, mask=coin_mask)
    plt.title('Izdvojen novcic')
    plt.imshow(coin)
    plt.show()

    cv2.imshow('Input slika', img.astype(np.uint8))
    cv2.imshow('Output maska', coin_mask.astype(np.uint8))
    cv2.imwrite('coin_mask.png', coin_mask)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
