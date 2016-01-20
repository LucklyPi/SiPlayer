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
    root = doc.createElement("LastFile");
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
    QDomElement root = doc.firstChildElement("filelist");
    if (root.isNull()) {
       file.remove();
       doc.clear();
       creatXML();
    }
}

void MyXML::save()
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
    newElement.setAttribute("fileclase", element.fileClass);
    newElement.setAttribute("lastposition", element.lastPosition);
    newElement.setAttribute("name", element.fileName);
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
                element->fileName       = fileName;
                element->lastPosition   = elt.attribute("lastposition").toLong();
                element->fileClass      = elt.attribute("fileclase").toInt();
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

bool MyXML::replaceElement(FileElement element)
{
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if (elt.attribute("name") == element.fileName) {
            elt.setAttribute("lastposition", element.lastPosition);
            return true;
        }
    }
    return false;
}

/**
 * @brief MyXML::getFileList 获取给定类别的所有文件的文件名列表
 * @param fileCalss 给定的类别，取值在0到9之间
 * @return 给定类别的所有文件的文件名列表
 */
QStringList MyXML::getFileList(int fileCalss)
{
    if(fileCalss < 0 || fileCalss > 9)
        fileCalss = 0;

    QStringList fileList;
    QDomElement filelist = doc.firstChildElement("filelist");
    QDomElement elt = filelist.firstChildElement("file");
    for (; !elt.isNull(); elt = elt.nextSiblingElement("file")) {
        if(fileCalss == 0 || elt.attribute("fileclase").toInt() == fileCalss)
            fileList.append(elt.attribute("name"));
    }
    return fileList;
}

void MyXML::setLastFile(FileElement element)
{
    QDomElement lastFile = doc.firstChildElement("LastFile");
    if(lastFile.isNull()) {
        lastFile = doc.createElement("LastFile");
        doc.appendChild(lastFile);
    }
    lastFile.setAttribute("fileclase", element.fileClass);
    lastFile.setAttribute("lastposition", element.lastPosition);
    lastFile.setAttribute("name", element.fileName);
}

QString MyXML::getLastFile()
{
    QDomElement lastFile = doc.firstChildElement("LastFile");
    if(lastFile.isNull()) {
        return "";
    } else {
        return lastFile.attribute("name");
    }
}

