#include <glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846
#define JERRY_HALF_WIDTH 0.05f // Setengah dari lebar Jerry (atur sesuai ukuran Jerry)


float jerryPosX = 0.0f; // Posisi X Jerry
bool isJumping = false; // Status apakah Jerry sedang melompat
float jumpHeight = 0.0f; // Ketinggian lompat
float jumpSpeed = 0.02f; // Kecepatan lompat

void drawSun() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.7f, 0.7f, 0.0f);
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();

    glColor3f(1.0f, 0.9f, 0.0f);
    float sunX = 0.7f;
    float sunY = 0.7f;
    float radius = 0.15f;
    int numRays = 12;

    for (int i = 0; i < numRays; ++i) {
        float angle = 2.0f * M_PI * i / numRays;
        float rayX1 = sunX + radius * cos(angle);
        float rayY1 = sunY + radius * sin(angle);
        float rayX2 = sunX + (radius + 0.1f) * cos(angle);
        float rayY2 = sunY + (radius + 0.1f) * sin(angle);

        glBegin(GL_LINES);
        glVertex2f(rayX1, rayY1);
        glVertex2f(rayX2, rayY2);
        glEnd();
    }
}

void drawGrass() {
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glEnd();
}

void drawTree(float x, float y) {
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05f, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.3f);
    glVertex2f(x - 0.05f, y + 0.3f);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.2f);
    glPushMatrix();
    glTranslatef(x, y + 0.35f, 0.0f);
    glutSolidSphere(0.15, 20, 20);
    glTranslatef(0.12f, -0.05f, 0.0f);
    glutSolidSphere(0.12, 20, 20);
    glTranslatef(-0.24f, 0.0f, 0.0f);
    glutSolidSphere(0.12, 20, 20);
    glPopMatrix();
}

void drawHouse(float x, float y) {
    // Badan rumah
    glColor3f(0.8f, 0.5f, 0.3f); // Warna coklat untuk badan rumah
    glBegin(GL_QUADS);
    glVertex2f(x - 0.1f, y);
    glVertex2f(x + 0.1f, y);
    glVertex2f(x + 0.1f, y + 0.15f);
    glVertex2f(x - 0.1f, y + 0.15f);
    glEnd();

    // Atap rumah
    glColor3f(0.6f, 0.3f, 0.2f); // Warna coklat tua untuk atap
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.12f, y + 0.15f);
    glVertex2f(x + 0.12f, y + 0.15f);
    glVertex2f(x, y + 0.25f);
    glEnd();

    // Pintu rumah
    glColor3f(0.3f, 0.2f, 0.1f); // Warna coklat tua untuk pintu
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f, y);
    glVertex2f(x + 0.02f, y);
    glVertex2f(x + 0.02f, y + 0.08f);
    glVertex2f(x - 0.02f, y + 0.08f);
    glEnd();
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);

    // Lingkaran utama awan
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glutSolidSphere(0.1, 20, 20);

    // Tambahan lingkaran awan untuk bentuk yang lebih organik
    glTranslatef(-0.1f, 0.0f, 0.0f); //lingakaran kiri
    glutSolidSphere(0.08, 20, 20);

    glTranslatef(0.2f, 0.0f, 0.0f); //lingkaran kanan
    glutSolidSphere(0.08, 20, 20);

    glPopMatrix();
}

void drawBackground() {
    drawGrass();
    drawSun();
    drawTree(-0.7f, -0.4f);
    drawTree(0.6f, -0.4f);
    drawHouse(0.0f, -0.4f);
    drawCloud(-0.5f, 0.7f);
    drawCloud(0.3f, 0.8f);
}

void drawEars() {
    glColor3f(0.8f, 0.6f, 0.4f);

    // Telinga kiri
    glPushMatrix();
    glTranslatef(-0.1f, 0.08f, 0.0f); // Lebih dekat ke kepala
    glutSolidSphere(0.03, 20, 20);
    glPopMatrix();

    // Telinga kanan
    glPushMatrix();
    glTranslatef(0.1f, 0.08f, 0.0f);
    glutSolidSphere(0.03, 20, 20);
    glPopMatrix();
}

void drawHead() {
    glColor3f(0.8f, 0.6f, 0.4f);
    glPushMatrix();
    glutSolidSphere(0.1, 30, 30);
    glPopMatrix();
}

void drawHair() {
    glColor3f(0.5f, 0.3f, 0.1f);

    // Rambut kiri
    glPushMatrix();
    glTranslatef(-0.02f, 0.1f, 0.05f); // Lebih dekat ke kepala
    glRotatef(30, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.02f, 0.04f); // Rambut lebih pendek
    glEnd();
    glPopMatrix();

    // Rambut tengah
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.05f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.04f);
    glEnd();
    glPopMatrix();

    // Rambut kanan
    glPushMatrix();
    glTranslatef(0.02f, 0.1f, 0.05f);
    glRotatef(-30, 0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.02f, 0.04f);
    glEnd();
    glPopMatrix();
}

void drawEyes() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.03f, 0.04f, 0.05f);
    glutSolidSphere(0.02, 20, 20);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.007f, 0.0f, 0.02f);
    glutSolidSphere(0.0075, 10, 10);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.03f, 0.04f, 0.05f);
    glutSolidSphere(0.02, 20, 20);
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(-0.007f, 0.0f, 0.02f);
    glutSolidSphere(0.0075, 10, 10);
    glPopMatrix();
}

void drawNose() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.02f, 0.05f);
    glutSolidSphere(0.015, 20, 20);
    glPopMatrix();
}

void drawMouth() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.01f, 0.05f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.02f, -0.01f);
    glVertex2f(0.0f, -0.025f);
    glVertex2f(0.02f, -0.01f);
    glEnd();
    glPopMatrix();
}

void drawBody() {
    glColor3f(0.8f, 0.6f, 0.4f);
    glPushMatrix();
    glTranslatef(0.0f, -0.125f, 0.0f);
    glScalef(1.0f, 1.2f, 1.0f);
    glutSolidSphere(0.07, 30, 30);
    glPopMatrix();
}

void drawArmsAndLegs() {
    glColor3f(0.8f, 0.6f, 0.4f);
    glPushMatrix();
    glTranslatef(-0.075f, -0.075f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.075f, -0.075f, 0.0f);
    glScalef(1.0f, 0.5f, 1.0f);
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.04f, -0.2f, 0.0f);
    glScalef(1.0f, 0.6f, 1.0f);
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.04f, -0.2f, 0.0f);
    glScalef(1.0f, 0.6f, 1.0f);
    glutSolidSphere(0.04, 20, 20);
    glPopMatrix();
}

void drawJerry() {
    glPushMatrix();
    glTranslatef(jerryPosX, -0.7f + jumpHeight, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f);
    drawEars();
    drawHead();
    drawHair();
    drawEyes();
    drawNose();
    drawMouth();
    drawBody();
    drawArmsAndLegs();
    glPopMatrix();
}

void update(int value) {
    if (isJumping) {
        jumpHeight += jumpSpeed;
        if (jumpHeight >= 0.2f || jumpHeight <= 0.0f) {
            jumpSpeed = -jumpSpeed;
        }
        if (jumpHeight <= 0.0f) {
            jumpHeight = 0.0f;
            isJumping = false;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Fungsi keyboard yang dimodifikasi
void keyboard(int key, int x, int y) {
    // Mendapatkan lebar dan tinggi jendela
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Menghitung batas kiri dan kanan Jerry dalam koordinat normalisasi
    float leftLimit = -1.0f + JERRY_HALF_WIDTH;
    float rightLimit = 1.0f - JERRY_HALF_WIDTH;

    switch (key) {
    case GLUT_KEY_LEFT:
        // Pastikan Jerry tidak melewati batas kiri
        if (jerryPosX > leftLimit) {
            jerryPosX -= 0.05f;
        }
        break;
    case GLUT_KEY_RIGHT:
        // Pastikan Jerry tidak melewati batas kanan
        if (jerryPosX < rightLimit) {
            jerryPosX += 0.05f;
        }
        break;
    case GLUT_KEY_UP:
        if (!isJumping) {         // Memulai lompatan jika Jerry tidak melompat
            isJumping = true;     // Menandakan status lompatan
            jumpSpeed = 0.02f;    // Kecepatan awal lompatan
        }
        break;
    }
    glutPostRedisplay();          // Memperbarui tampilan
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawJerry();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Jerry Moving and Jumping in OpenGL");
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}