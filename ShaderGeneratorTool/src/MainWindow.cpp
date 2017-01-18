#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
  // vert shader updates
  connect(m_ui->s_loadVertexShader,SIGNAL(clicked(bool)),this,SLOT(vertexShaderClicked()));
  connect(this,SIGNAL(vertexShaderChanged(const QString &)),m_gl,SLOT(loadVertexShader(const QString &)));
  // frag shader updates
  connect(m_ui->s_loadFragmentShader,SIGNAL(clicked(bool)),this,SLOT(fragmentShaderClicked()));
  connect(this,SIGNAL(fragmentShaderChanged(const QString &)),m_gl,SLOT(loadFragmentShader(const QString &)));
  // progam name changes
  connect(m_ui->m_programName,SIGNAL(textChanged(QString)),m_gl,SLOT(programNameChanged(const QString &)));
  //connect(this,SIGNAL(programNameChanged(const QString &)),m_gl,SLOT(programNameChanged(const QString &)));
  // create shader changes
  connect(m_ui->s_createShader,SIGNAL(clicked(bool)),m_gl,SLOT(createShaderProgram()));
  connect(m_gl,SIGNAL(updateDebug(QString)),m_ui->m_debugOutput,SLOT(setPlainText(QString)));

  // export class
  connect(m_ui->s_exportClass,SIGNAL(clicked(bool)),this,SLOT(exportClassClicked()));
  connect(this,SIGNAL(exportClass(const QString , bool )),m_gl,SLOT(exportClass(const QString , bool )));



}



void MainWindow::exportClassClicked()
{
  QString dir = QFileDialog::getExistingDirectory(nullptr, tr("Open Directory"),
                                                  "",
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);
  emit exportClass(dir,m_ui->m_generateBaseClass);
}


void MainWindow::vertexShaderClicked()
{
  QString fileName = QFileDialog::getOpenFileName(nullptr,
      tr("Open Vertex Shader"), "r", tr("Shader Files (*.glsl)"));

  if(fileName !=nullptr)
  {

    m_ui->s_vertShaderName->setText(fileName);
    emit vertexShaderChanged(fileName);
  }
}

void MainWindow::fragmentShaderClicked()
{
  QString fileName = QFileDialog::getOpenFileName(nullptr,
      tr("Open Vertex Shader"), "r", tr("Shader Files (*.glsl)"));

  if(fileName !=nullptr)
  {

    m_ui->s_fragmentShaderName->setText(fileName);
    emit fragmentShaderChanged(fileName);
  }
}

void MainWindow::programNameChanged()
{
  emit programNameChanged(m_ui->m_programName->text());
}

MainWindow::~MainWindow()
{
}

