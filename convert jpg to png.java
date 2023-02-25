import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class JpgToPngConverter {
    public static void main(String[] args) {
        String jpgFilename = "input.jpg";
        String pngFilename = "output.png";

        try {
            // Read the input JPG image
            BufferedImage image = ImageIO.read(new File(jpgFilename));

            // Write the output PNG image
            File output = new File(pngFilename);
            ImageIO.write(image, "png", output);

            System.out.println("Conversion complete!");
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
