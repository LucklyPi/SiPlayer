#include "myxml.h"

#include <QFile>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QTextStream>
#include <QFileInfo>
#include <QDomNodeList>

#include <QDebug>

MyXML::MyXML(QString fileNmae)
{
    if(fileNmae.isEmpty())
        return;
    saveFileName = fileNmae;

    QFileInfo fileInfo(saveFileName);
    if(fileInfo.exists() && fileInfo.isFile())
        loadXML();  //文件存在，载入文件
    else
        creatXML(); //文件不存在，新创建一个文件
}

MyXML::~MyXML()
{

}

void MyXML::creatXML()
{
    if(saveFileName.isEmpty())
        return;

    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"GB2312\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("filelist");
    doc.appendChild(root);

    QFile file(saveFileName);
    file.open(QIODevice::ReadWrite);
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
        doc.clear();
        creatXML();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if (root.tagName() != "filelist") {
       file.remove();
       doc.clear();
       creatXML();
    }
}

void MyXML::saveXMLtoFile()
{
    if(saveFileName.isEmpty())
        return;
    QFile file(saveFileName);
    file.resize(0);
    if(!file.open(QIODevice::ReadWrite))
        return;
    QTextStream out(&file);
    doc.save(out,4);
    file.close();
}

void MyXML::addElement(FileElement element)
{
    if(getElement(element.fileName,NULL))
        return;
    QDomElement newElement = doc.createElement("file");
    newElement.setAttribute("lastposition", element.lastPosition);
    newElement.setAttribute("name", element.fileName);

    QDomElement fileClase = doc.createElement("fileclase");
    QDomText t = doc.createTextNode(QString::number(element.fileClass));
    fileClase.appendChild(t);
    newElement.appendChild(fileClase);

    QDomElement filelist = doc.firstChildElement("filelist");
    filelist.appendChild(newElement);

}

bool MyXML::getElement(QString fileName, FileElement *element)
{
    if (fileName.isEmpty())
        return false;
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if (elt.attribute("name") == fileName) {
            if (element) {
                element->fileName = fileName;
                element->lastPosition = elt.attribute("lastposition").toLong();
                element->fileClass = elt.firstChildElement("lastposition").text().toInt();
            }
            return true;
        }
    }
    return false;
}

void MyXML::removeElement(QString fileName)
{
    if (fileName.isEmpty())
        return;
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if (elt.attribute("name") == fileName) {
            filelist.removeChild(elt);
        }
    }
}

void MyXML::replaceElement(FileElement element)
{
    QDomElement newElement = doc.createElement("file");
    newElement.setAttribute("name", element.fileName);
    newElement.setAttribute("lastposition", element.lastPosition);

    QDomElement fileClase = doc.createElement("fileclase");
    QDomText t = doc.createTextNode(QString::number(element.fileClass));
    fileClase.appendChild(t);
    newElement.appendChild(fileClase);

    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if (elt.attribute("name") == element.fileName) {
            filelist.replaceChild(newElement,elt);
        }
    }
}

QStringList MyXML::getFileList()
{
    QStringList fileList;
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        fileList.append(elt.attribute("name"));
    }
    return fileList;
}
