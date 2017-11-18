<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="student">
    <html>
    <head>
        <title>XLST demo</title>
    </head>
    <body>
        <h2>Vtu student description</h2>
        USN:<span style="color:red"><xsl:value-of select="usn"/></span><br/>
        Name:<span style="color:purple"><xsl:value-of select="name"/></span><br/>
        College:<span style="color:blue"><xsl:value-of select="college"/></span><br/>
        Branch:<span style="color:indigo"><xsl:value-of select="branch"/></span><br/>
        Email:<span style="color:yellow"><xsl:value-of select="email"/></span><br/>
        Joinyear:<span style="color:orange"><xsl:value-of select="joinyear"/></span><br/>
    </body>
</html>
</xsl:template>
</xsl:stylesheet>
