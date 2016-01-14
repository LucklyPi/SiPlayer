#include "myxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QTextStream>
#include <QFileInfo>

#include <QDebug>

MyXML::MyXML()
{

}

MyXML::MyXML(const QString fileNmae)
{
    if(fileNmae.isEmpty())
        return;
    saveFileName = fileNmae;

    QFileInfo fileInfo(saveFileName);
    if(fileInfo.exists() && fileInfo.isFile())
        loadXML();
    else
        creatXML();
}


MyXML::~MyXML()
{

}

void MyXML::creatXML()
{
    if(saveFileName.isEmpty())
        return;

    QFile file(saveFileName);
    file.open(QIODevice::ReadWrite);

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"GB2312\"");
    doc.appendChild(instruction);

    QDomElement root = doc.createElement("filelist");
    doc.appendChild(root);
    QDomText text = doc.createTextNode("\n");
    root.appendChild(text);

    root.appendChild(text);
    QTextStream out(&file);
    doc.save(out,4);

    file.close();
}


void MyXML::loadXML()
{
    QFile file(saveFileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        file.remove();
        creatXML();
        return;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        file.close();
        file.remove();
        creatXML();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.tagName() != "filelist") {
       file.remove();
       creatXML();
    }
    qDebug()<<"root.text() = "<<root.text();
}



