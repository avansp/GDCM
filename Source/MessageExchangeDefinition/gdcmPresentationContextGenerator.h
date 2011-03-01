/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMPRESENTATIONCONTEXTGENERATOR_H
#define GDCMPRESENTATIONCONTEXTGENERATOR_H

#include "gdcmDirectory.h"
#include "gdcmPresentationContext.h"

namespace gdcm
{

namespace network
{

/**
 * \brief PresentationContextGenerator
 * This class is responsible for generating the proper PresentationContext that
 * will be used in subsequent operation during a DICOM Query/Retrieve
 * association.  the step of the association is very sensible as special care
 * need to be taken to explicitely define what instance are going to be send
 * and how they are encoded.
 *
 * For example a PresentationContext will express that negotiation requires
 * that CT Image Storage are send using JPEG Lossless, while US Image Storage
 * are sent using RLE Transfer Syntax.
 *
 * Two very different API are exposed one which will always default to little
 * endian transfer syntax see GenerateFromUID()
 * This API is used for C-ECHO, C-FIND and C-MOVE (SCU).
 * Another API: GenerateFromFilenames() is used for C-STORE (SCU) as it will
 * loop over all filenames argument to detect the actual encoding. and
 * therefore find the proper encoding to be used.
 *
 * \see PresentationContext
 */
class GDCM_EXPORT PresentationContextGenerator
{
public:
  PresentationContextGenerator();

  // Set MergeMode
  // Default mode, each pair AbstractSyntax/TransferSyntax are only merged when
  // exactly identical
  void SetMergeModeToAbstractSyntax();

  // Set MergeMode
  // Merge is done on a per AbstractSyntax basis. Any new TransferSyntax for a
  // given AbstractSyntax is merge to the existing PresentationContext refering
  // to that AbstractSyntax
  void SetMergeModeToTransferSyntax();

  /// Generate the PresentationContext array from a UID (eg. VerificationSOPClass)
  bool GenerateFromUID(UIDs::TSName tsname);

  /// Generate the PresentationContext array from a File-Set. File specified needs to
  /// be valid DICOM files.
  bool GenerateFromFilenames(const Directory::FilenamesType &files);

  typedef std::vector<PresentationContext> PresentationContextArrayType;
  typedef PresentationContextArrayType::size_type SizeType;
  PresentationContextArrayType const &GetPresentationContexts() { return PresContext; }

protected:
  bool AddPresentationContext( AbstractSyntax const & as, TransferSyntaxSub const & ts );

private:
  std::vector<PresentationContext> PresContext;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXTGENERATOR_H
